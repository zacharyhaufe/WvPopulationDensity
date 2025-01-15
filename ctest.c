/**
 * @file ctest.c
 * @brief Source code file for WVU CTest testing framework
 * @author Brian Powell
 * @version 1.5
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 *
 * Requries the following linker flags for GCC in Visual Studio:
 * -Wl,--no-as-needed -ldl
 *
 * No linker flags required for Xcode.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "ctest.h"
#include <stdbool.h>
#include <regex.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>

// OS-specific includes
#ifdef __APPLE__
	#include <malloc/malloc.h>
#else
	#include <malloc.h>
#endif

// Use GNU source code for redirecting output and overwriting functions
#define _GNU_SOURCE

// Define file to store capture output - comment out to not capture output
#define CAPTURE_OUTPUT "captured_output.txt"

char* add_regex_anchors(const char* pattern)
{
	// Determine length of search pattern
	size_t pattern_length = strlen(pattern);
	size_t anchored_pattern_length = pattern_length + 2; // Add 2 for ^ and $

	// Malloc memory for new anchored
	char* anchored_pattern = (char*)malloc(anchored_pattern_length + 1); // +1 for null terminator
	if (anchored_pattern == NULL)
	{
		fprintf(stderr, "Could not allocate memory: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Build anchored pattern
	anchored_pattern[0] = '^';
	strncpy(anchored_pattern + 1, pattern, pattern_length);
	anchored_pattern[anchored_pattern_length - 1] = '$';
	anchored_pattern[anchored_pattern_length] = '\0';

	return anchored_pattern;
}

bool are_equals_regex(const char* pattern, const char* string)
{
	// Add anchors to regex pattern to ensure full match
	pattern = add_regex_anchors(pattern);

	// Call is_contained function
	return is_contained_regex(pattern, string);
}

char* build_path(const char* directory, const char* filename)
{
	// Build path incorporating directory and specified file
	char* path = (char*)malloc(strlen(directory) + strlen(filename) + 1);
	if (path == NULL)
	{
		fprintf(stderr, "Could not allocate memory: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Concatenate directory and path
	strcpy(path, directory);
	strcat(path, filename);

	return path;
}

char* clean_newlines(const char* input)
{
	// Loop to replace \r\n with \n
	char* cleaned_newlines = duplicate_string(input);
	char* newline = strstr(cleaned_newlines, "\r\n");
	while (newline != NULL) {
		// Move rest of string up one position
		memmove(newline, newline + 1, strlen(cleaned_newlines) - (size_t)(newline - cleaned_newlines) + 1 + 1); // Add 1 to include null terminator
		newline = strstr(cleaned_newlines, "\r\n");
	}

	return cleaned_newlines;
}

char* clean_string(const char* input, enum text_matching text_matching_options)
{
	// Return NULL if string is NULL
	if (input == NULL) {
		return NULL;
	}

	// If text_matching is 0, set to flexible matching
	if (text_matching_options == 0) {
		text_matching_options = FLEXIBLE;
	}

	// Always strip whitespace
	char* cleaned = duplicate_string(input);
	char* end = cleaned + strlen(cleaned) - 1;
	while (end > cleaned && isspace((unsigned char)*end)) {
		*end-- = '\0';
	}

	// Always clean up newlines
	cleaned = clean_newlines(cleaned);

	// If flexible matching, add all sub-options
	if (text_matching_options & FLEXIBLE) {
		text_matching_options |= IGNORE_CASE | IGNORE_PUNCTUATION | IGNORE_WHITESPACE | IGNORE_LINE_BREAKS | IGNORE_PERIODS | IGNORE_PUNCTUATION;
	}

	// If ignore case, convert to lower
	if (text_matching_options & IGNORE_CASE) {
		for (int i = 0; cleaned[i]; i++) {
			cleaned[i] = (char)tolower((unsigned char)cleaned[i]);
		}
	}

	// If ignore whitespace, remove spaces
	if (text_matching_options & IGNORE_WHITESPACE) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (!isspace((unsigned char)*src)) {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	// If ignore line breaks, remove newlines
	if (text_matching_options & IGNORE_LINE_BREAKS) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (*src != '\n') {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	// If ignore periods, remove periods
	if (text_matching_options & IGNORE_PERIODS) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (*src != '.') {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	// If ignore punctuation, remove punctuation
	if (text_matching_options & IGNORE_PUNCTUATION) {
		char* src = cleaned;
		char* dst = cleaned;
		while (*src != '\0') {
			if (!ispunct((unsigned char)*src)) {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

	return cleaned;
}

size_t ctest_get_malloc_size(void* ptr)
{
	// See if pointer is valid
	if (ptr == NULL)
	{
		return 0;
	}

	// If pointer is 0xFFFFFFFFFFFFFFFF, indicating memory was not set to anything, return size as 0
	if (ptr == (void*)0xFFFFFFFFFFFFFFFF)
	{
		return 0;
	}

	// Get size
#ifdef __APPLE__ 
	return malloc_size(ptr);
#else 
	return malloc_usable_size(ptr);
#endif 
}

bool does_file_exist(const char* path)
{
	// Attempt to open file
	FILE* filePtr = fopen(path, "r");

	// See if file exists
	if (filePtr != NULL) {
		// File exists

		// Close file
		fclose(filePtr);
		filePtr = NULL;

		return true; // File exists
	}
	else {
		// File does not exist
		return false;
	}
}

char* duplicate_string(const char* string) {
	// Return NULL if string is NULL
	if (string == NULL) {
		return NULL;
	}

	// Allocate memory for the new string
	char* duplicatePtr = (char*)malloc(strlen(string) + 1);
	if (duplicatePtr == NULL) {
		// Memory allocation failed
		return NULL;
	}

	// Copy the original string to the new memory location
	strcpy(duplicatePtr, string);

	return duplicatePtr;
}

bool file_contains_regex(const char* pattern, const char* path)
{
	// Read file
	char* file_contentsPtr = read_file(path);

	// Check file contents
	bool contains = is_contained_regex(pattern, file_contentsPtr);

	// Free memory from file contents
	free(file_contentsPtr);
	file_contentsPtr = NULL;

	return contains;
}

bool captured_output_contains_regex(const char* pattern)
{
	// Get file output
	char* captured_output = get_captured_output();

	// Check file contents
	bool contains = is_contained_regex(pattern, captured_output);

	// Free memory from file contents
	free(captured_output);
	captured_output = NULL;

	return contains;
}

char* get_directory(const char* path)
{
	// String to contain directory path
	char* directory = NULL;

	// Find location of last slash
	char* lastSlash = strrchr(path, '/');

	// If slash was found, use it to isolate directory name from path
	if (lastSlash != NULL)
	{
		size_t directoryLength = (size_t)(lastSlash - path + 1);
		directory = (char*)malloc(directoryLength + 1);
		strncpy(directory, path, directoryLength);
		directory[directoryLength] = '\0';
	}

	return directory;
}

size_t get_file_size(const char* path)
{
	// Attempt to open file.
	FILE* filePtr = fopen(path, "r");
	if (filePtr == NULL) {
		fprintf(stderr, "File %s not found.", path);
		exit(EXIT_FAILURE);
	}

	// Determine size of file
	fseek(filePtr, 0, SEEK_END);
	size_t file_size = (size_t)ftell(filePtr);

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	return file_size;
}

bool is_contained_regex(const char* pattern, const char* string)
{
	// Compile regex pattern
	regex_t regex;
	int result = regcomp(&regex, pattern, REG_EXTENDED);
	if (result != 0) {
		// An error occurred

		// Build and display error message
		char errorBuffer[100];
		regerror(result, &regex, errorBuffer, sizeof(errorBuffer));
		fprintf(stderr, "Regex compilation error: %s\n", errorBuffer);
		regfree(&regex);

		return false;
	}

	// Attempt to match regex
	result = regexec(&regex, string, 0, NULL, 0);
	regfree(&regex);

	// Determine if pattern matched string
	if (result == 0) {
		return true;
	}
	else if (result == REG_NOMATCH) {
		return false;
	}
	else {
		// Build and display error message
		char errorBuffer[100];
		regerror(result, &regex, errorBuffer, sizeof(errorBuffer));
		fprintf(stderr, "Regex matching error: %s\n", errorBuffer);

		return false;
	}
}

/**
 * @brief Tracks the location of original malloc function
 */
static void* (*real_malloc)(size_t) = NULL;

/**
 * @brief Overriden version of malloc to initialize memory to 0xFFFFFFFFFFFFFFFF
 * @param size Number of bytes requested
 * @return Pointer to allocated memory or NULL if allocation failed
 */
void* malloc(size_t size)
{
	// Store original malloc function prior to remapping
	if (real_malloc == NULL)
	{
		// Locate original malloc function
		real_malloc = dlsym(RTLD_NEXT, "malloc");

		// Check for errors
		if (real_malloc == NULL)
		{
			fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
		}
	}

	// Pointer to new memory
	void* memoryPtr = NULL;

	// Call original malloc function
	memoryPtr = real_malloc(size);

	// If memory was allocated, set it to 0xFFFFFFFFFFFFFFFF
	if (memoryPtr != NULL)
	{
		memset(memoryPtr, 0xFF, size);
	}

	return memoryPtr;
}

char* read_file(const char* path)
{
	// Get file size
	size_t file_size = get_file_size(path);

	// Attempt to open file.
	FILE* filePtr = fopen(path, "r");
	if (filePtr == NULL) {
		fprintf(stderr, "File %s not found.", path);
		exit(EXIT_FAILURE);
	}

	// Malloc memory for file
	char* buffer = (char*)malloc(file_size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Could not allocate memory: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Read file contents
	size_t bytesRead = fread(buffer, 1, file_size, filePtr);
	if (bytesRead != file_size) {
		fprintf(stderr,"Error reading file: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Null terminate string
	buffer[file_size] = '\0';

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	return buffer;
}

char* read_source_code_file(const char* filename)
{
	// Get directory this source code file is in
	char* directory = get_directory(__FILE__);

	// Build path incorporating directory and specified file
	char* path = build_path(directory, filename);

	// Read file
	char* source_code = read_file(path);

	// Free path info
	free(path);
	path = NULL;
	free(directory);
	directory = NULL;

	// Return file
	return source_code;
}

char* write_file(const char* path, const char* contents, bool overwrite)
{
	// If file exists, check if we should overwrite
	FILE* filePtr = fopen(path, "r");
	char* oldContents = NULL;
	if (filePtr != NULL) {
		fclose(filePtr);

		// Load existing contents of file
		oldContents = read_file(path);

		if (!overwrite) {
			// Print error message
			fprintf(stderr, "File %s already exists. Function was set to not overwrite.\n", path);
			
			return NULL;
		}
	}

	// Write contents to file
	filePtr = fopen(path, "w");
	if (filePtr == NULL) {
		// Print error message
		fprintf(stderr, "Error writing to file %s: %s.\n", path, strerror(errno));
		
		exit(EXIT_FAILURE);
	}

	// Write to file
	fputs(contents, filePtr);

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	return oldContents;
}

#ifdef CAPTURE_OUTPUT
int printf(const char* __restrict __fmt, ...)
{
	// Open file for storing output
	FILE* filePtr = fopen(CAPTURE_OUTPUT, "a");
	if (filePtr == NULL)
	{
		fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Use variadic arguments to print to file
	va_list args_file;
	va_start(args_file, __fmt);
	vfprintf(filePtr, __fmt, args_file);
	va_end(args_file);

	// Use variadic arguments to print to screen
	va_list args_screen;
	va_start(args_screen, __fmt);
	int printf_return = vprintf(__fmt, args_screen);
	va_end(args_screen);

	// Close captured output file
	fclose(filePtr);
	filePtr = NULL;

	return printf_return;
}

int puts(const char* __s)
{
	return printf("%s\n", __s);
}

/**
 * @brief Tracks the location of original fprintf function
 */
static int (*real_fprintf)(FILE* __stream, const char*, ...) = NULL;

int fprintf(FILE* __restrict __stream, const char* __restrict __fmt, ...)
{
	// Store original malloc function prior to remapping
	if (real_fprintf == NULL)
	{
		// Locate original malloc function
		real_fprintf = dlsym(RTLD_NEXT, "fprintf");

		// Check for errors
		if (real_fprintf == NULL)
		{
			real_fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
		}
	}

	// Use variadic arguments to print to screen
	va_list args_screen;
	va_start(args_screen, __fmt);
	int fprintf_return = vfprintf(__stream, __fmt, args_screen);
	va_end(args_screen);

	// Print to file if target was stdout or stderr
	if (__stream == stdout || __stream == stderr)
	{
		// Open file for storing output
		FILE* filePtr = fopen(CAPTURE_OUTPUT, "a");
		if (filePtr == NULL)
		{
			real_fprintf(stderr, "Error opening file for writing: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		// Use variadic arguments to print to file
		va_list args_file;
		va_start(args_file, __fmt);
		vfprintf(filePtr, __fmt, args_file);
		va_end(args_file);

		// Close captured output file
		fclose(filePtr);
		filePtr = NULL;
	}

	return fprintf_return;
}

char* get_captured_output(void)
{
	#ifndef CAPTURE_OUTPUT
		fprintf(stderr, "Output is not being captured.\n");
		return NULL;
	#else
		// Check to see if file exists
		if (!does_file_exist(CAPTURE_OUTPUT))
		{
			fprintf(stderr, "File %s does not exist.\n", CAPTURE_OUTPUT);
			return NULL;
		}

		// Read file
		char* file_contentsPtr = read_file(CAPTURE_OUTPUT);

		// Return file contents
		return file_contentsPtr;
	#endif
}
#endif