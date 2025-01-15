/**
 * @file ctest.h
 * @brief Header file for WVU CTest testing framework
 * @author Brian Powell
 * @version 1.5
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

#pragma once

// Use GNU source for kill and usleep functions
#define _GNU_SOURCE

// Patch IntelliSense issues for _Float types on Visual Studio with WSL
#ifdef __INTELLISENSE__
    #ifndef INTELLISENSE_FLOAT_FIX
        #define INTELLISENSE_FLOAT_FIX 1
        typedef float _Float32;
        typedef double _Float64;
        typedef long double _Float128;
        typedef double _Float32x;
        typedef long double _Float64x;
    #endif
#endif

// Include header files
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>

 // Define constants
#define EXIT_TEST_FAILED 99
#define EXIT_UNEXPECTED_RETURN_VALUE 98
#define EXIT_UNRELATED_FAILURE 97
#define EXIT_NOT_IMPLEMENTED 96
#define	EXIT_MALLOC_FAILED 95
#define EXIT_SHM_FAILED 94
#define EXIT_FORK_FAILED 93
#define EXIT_UNEXPECTED_NULL 92

// Define timeout for waiting for forked processes when testing functions
#ifndef TIMEOUT_SECONDS
    #define TIMEOUT_SECONDS 2
#endif

// Define number of microseconds to sleep when waiting for forked processes
#ifndef SLEEP_MICROSECONDS
    #define SLEEP_MICROSECONDS 5 // Default: 5
#endif

// Define whether to wait for forked processes without looping - 0: False, 1: True
#ifndef WAIT_FOR_FORKED_PROCESS_WITHOUT_LOOPING
    #define WAIT_FOR_FORKED_PROCESS_WITHOUT_LOOPING 0 // False
#endif

/*
 * Settings for text matching
*/
enum text_matching {
	EXACT = 1,
	FLEXIBLE = 2,
	IGNORE_CASE = 4,
	IGNORE_WHITESPACE = 8,
	IGNORE_LINE_BREAKS = 16,
	IGNORE_PERIODS = 32,
	IGNORE_PUNCTUATION = 64
};

// Define macros
/**
 * @brief Macro for calling function that returns a double in a forked process
 */
#define CALL_FUNCTION_DOUBLE(function_name, args...) CALL_FUNCTION_PRIMITIVE(function_name, double, args)

 /**
  * @brief Macro for calling function that returns a double in a fork process, returning its return value
  */
#define CALL_FUNCTION_DOUBLE_WITH_RETURN(function_name,  args...) CALL_FUNCTION_PRIMITIVE_WITH_RETURN(function_name, double, args)

  /**
  * @brief Macro for calling function that returns an int in a forked process
  */
#define CALL_FUNCTION_INT(function_name, args...) CALL_FUNCTION_PRIMITIVE(function_name, int, args)

  /**
   * @brief Macro for calling function that returns an int in a fork process, returning its return value
   */
#define CALL_FUNCTION_INT_WITH_RETURN(function_name,  args...) CALL_FUNCTION_PRIMITIVE_WITH_RETURN(function_name, int, args)

   /**
	* @brief Macro for calling function that returns a numeric value in a forked process
	*/
#define CALL_FUNCTION_PRIMITIVE(function_name, type_name, args...) \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        type_name result = (type_name) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        type_name test; \
        memcpy(&test, &result, sizeof(type_name)); \
        \
        WAIT_FOR_CHILDREN(function_name); \
        \
        exit(0); \
    } \
    else \
    { \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
    } \
} while(0)

/**
	* @brief Macro for calling function that returns a numeric value in a forked process, returning the value
	*/
#define CALL_FUNCTION_PRIMITIVE_WITH_RETURN(function_name, type_name, args...) \
type_name return_value_##function_name; \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    key_t shm_key = (key_t) rand(); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        int shm_id = shmget(shm_key, sizeof(type_name), IPC_CREAT | 0666); \
		if (shm_id == -1) \
		{ \
			exit(EXIT_SHM_FAILED); \
		} \
		type_name* sharedPtr = (type_name*) shmat(shm_id, NULL, 0); \
		if (sharedPtr == (void*) -1) \
		{ \
            exit(EXIT_SHM_FAILED); \
        } \
        type_name result = (type_name) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        memcpy(sharedPtr, &result, sizeof(type_name)); \
        shmdt(sharedPtr); \
        \
        WAIT_FOR_CHILDREN(function_name); \
        \
        exit(0); \
    } \
    else \
    { \
        int shm_id = shmget(shm_key, sizeof(type_name), IPC_CREAT | 0666); \
        TEST_ASSERT_NOT_EQUAL_MESSAGE(shm_id, -1, "Shared memory could not be created."); \
        \
		type_name* sharedPtr = (type_name*) shmat(shm_id, NULL, 0); \
        TEST_ASSERT_NOT_EQUAL_MESSAGE(sharedPtr, (void*) -1, "Shared memory could not be attached."); \
        \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
        \
		memcpy(&return_value_##function_name, sharedPtr, sizeof(type_name)); \
        \
		shmdt(sharedPtr); \
		shmctl(shm_id, IPC_RMID, NULL); \
    } \
} while(0)

/**
 * @brief Macro for calling function that returns a pointer in a forked process
 */
#define CALL_FUNCTION_POINTER(function_name, args...) \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        void* resultPtr = (void*) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        if (resultPtr == NULL) \
		{ \
			exit(0); \
		} \
        void* testPtr = malloc(ctest_get_malloc_size(resultPtr)); \
        if (testPtr == NULL) \
        { \
            exit(EXIT_MALLOC_FAILED); \
        } \
        \
        memcpy(testPtr, resultPtr, ctest_get_malloc_size(resultPtr)); \
		\
        free(testPtr); \
        testPtr = NULL; \
        \
        WAIT_FOR_CHILDREN(function_name); \
        \
        exit(0); \
    } \
    else \
    { \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
    } \
} while(0)

/**
 * @brief Macro for calling function that returns a pointer that is not to be NULL in a forked process
 */
#define CALL_FUNCTION_POINTER_NOT_NULL(function_name, args...) \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        void* resultPtr = (void*) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        if (resultPtr == NULL) \
		{ \
			exit(EXIT_UNEXPECTED_NULL); \
		} \
        void* testPtr = malloc(ctest_get_malloc_size(resultPtr)); \
        if (testPtr == NULL) \
        { \
            exit(EXIT_MALLOC_FAILED); \
        } \
        \
        memcpy(testPtr, resultPtr, ctest_get_malloc_size(resultPtr)); \
		\
        free(testPtr); \
        testPtr = NULL; \
        \
        WAIT_FOR_CHILDREN(function_name); \
		\
        exit(0); \
    } \
    else \
    { \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
    } \
} while(0)

/**
 * @brief Macro for calling function that returns a numeric value in a forked process, returning the value
 */
#define CALL_FUNCTION_POINTER_WITH_RETURN(function_name, args...) \
void* return_value_##function_name = NULL; \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    key_t shm_key = (key_t) rand(); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        int shm_id = shmget(shm_key, sizeof(void*), IPC_CREAT | 0666); \
		if (shm_id == -1) \
		{ \
			exit(EXIT_SHM_FAILED); \
		} \
		type_name* sharedPtr = (type_name*) shmat(shm_id, NULL, 0); \
		if (sharedPtr == (void*) -1) \
		{ \
            exit(EXIT_SHM_FAILED); \
        } \
        void* result = (void*) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        memcpy(sharedPtr, &result, sizeof(void*)); \
        shmdt(sharedPtr); \
        \
        WAIT_FOR_CHILDREN(function_name); \
        \
        exit(0); \
    } \
    else \
    { \
        int shm_id = shmget(shm_key, sizeof(void*), IPC_CREAT | 0666); \
        TEST_ASSERT_NOT_EQUAL_MESSAGE(shm_id, -1, "Shared memory could not be created."); \
        \
		void* sharedPtr = (void*) shmat(shm_id, NULL, 0); \
        TEST_ASSERT_NOT_EQUAL_MESSAGE(sharedPtr, (void*) -1, "Shared memory could not be attached."); \
        \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
		\
		memcpy(&return_value_##function_name, sharedPtr, sizeof(void*)); \
        \
		shmdt(sharedPtr); \
		shmctl(shm_id, IPC_RMID, NULL); \
    } \
} while(0)

/**
 * @brief Macro for calling function that returns a string in a forked process
 */
#define CALL_FUNCTION_STRING(function_name, args...) \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        char* resultPtr = (char*) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
		if (resultPtr == NULL) \
		{ \
			exit(0); \
		} \
        \
        char* testPtr = malloc(strlen(resultPtr) + 1); \
        if (testPtr == NULL) \
        { \
            exit(EXIT_MALLOC_FAILED); \
        } \
        \
        size_t result_size = strlen(resultPtr); \
        memset(testPtr, 0, strlen(resultPtr) + 1); \
        strncpy(testPtr, resultPtr, strlen(resultPtr)); \
        result_size = result_size - 1; \
		\
        free(testPtr); \
        testPtr = NULL; \
        \
        WAIT_FOR_CHILDREN(function_name); \
		\
        exit(0); \
    } \
    else \
    { \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
    } \
} while(0)

/**
 * @brief Macro for calling function that returns a numeric value in a forked process, returning the value
 */
#define CALL_FUNCTION_STRING_WITH_RETURN(function_name, string_size, args...) \
char* return_value_##function_name = NULL; \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    key_t shm_key = (key_t) rand(); \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    if (child_pid == 0) \
    { \
        int shm_id = shmget(shm_key, sizeof(string_size), IPC_CREAT | 0666); \
		if (shm_id == -1) \
		{ \
			exit(EXIT_SHM_FAILED); \
		} \
		char* sharedPtr = (char*) shmat(shm_id, NULL, 0); \
		if (sharedPtr == (void*) -1) \
		{ \
            exit(EXIT_SHM_FAILED); \
        } \
        char* result = (char*) function_name(args); \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        strncpy(sharedPtr, result, string_size); \
        \
        free(result); \
        result = NULL; \
		\
        shmdt(sharedPtr); \
        \
        WAIT_FOR_CHILDREN(function_name); \
        \
        exit(0); \
    } \
    else \
    { \
        int shm_id = shmget(shm_key, sizeof(void*), IPC_CREAT | 0666); \
        TEST_ASSERT_NOT_EQUAL_MESSAGE(shm_id, -1, "Shared memory could not be created."); \
		\
		char* sharedPtr = (char*) shmat(shm_id, NULL, 0); \
        TEST_ASSERT_NOT_EQUAL_MESSAGE(sharedPtr, (void*) -1, "Shared memory could not be attached."); \
		\
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
		\
        return_value_##function_name = malloc(string_size); \
        TEST_ASSERT_NOT_NULL_MESSAGE(return_value_##function_name, "Memory could not be allocated for return value."); \
		strncpy(return_value_##function_name, sharedPtr, string_size); \
		\
		shmdt(sharedPtr); \
		shmctl(shm_id, IPC_RMID, NULL); \
    } \
} while(0)

/**
 * @brief Macro for calling function that returns a struct in a forked process
 */
#define CALL_FUNCTION_STRUCT(function_name, struct_type_name, args...) CALL_FUNCTION_PRIMITIVE(function_name, struct_type_name, args)

/**
 * @brief Macro for calling function that returns a struct in a forked process, with return value
 */
#define CALL_FUNCTION_STRUCT_WITH_RETURN(function_name, struct_type_name, args...) CALL_FUNCTION_PRIMITIVE_WITH_RETURN(function_name, struct_type_name, args)

/**
 * @brief Macro for calling function that returns an unsigned int in a forked process
 */
#define CALL_FUNCTION_UNSIGNED_INT(function_name, args...) CALL_FUNCTION_PRIMITIVE(function_name, unsigned int, args)

/**
 * @brief Macro for calling function that returns an unsigned int in a forked process, with return value
 */
#define CALL_FUNCTION_UNSIGNED_INT_WITH_RETURN(function_name, args...) CALL_FUNCTION_PRIMITIVE_WITH_RETURN(function_name, unsigned int, args)

/**
 * @brief Macro for calling function that returns nothing in a forked process
 */
#define CALL_FUNCTION_VOID(function_name, args...) \
do { \
    TEST_ASSERT_FALSE_MESSAGE(not_implemented_##function_name, "The " #function_name " function has not been implemented."); \
    \
    pid_t child_pid = fork(); \
    if (child_pid < 0) \
    { \
        TEST_FAIL_MESSAGE("Could not fork child process."); \
    } \
    \
    if (child_pid == 0) \
    { \
        function_name(args); \
        \
        if (not_implemented_##function_name) \
        { \
            exit(EXIT_NOT_IMPLEMENTED); \
        } \
        \
        WAIT_FOR_CHILDREN(function_name); \
		\
        exit(0); \
    } \
    else \
    { \
        WAIT_FOR_CHILD_PID(child_pid, function_name); \
    } \
} while(0)

/**
 * @brief Macro for waiting for a child process to terminate
 */
#define WAIT_FOR_CHILD_PID(child_pid, function_name) \
time_t start_time = time(NULL); \
int child_return = -1; \
\
do \
{ \
    pid_t result; \
    if (WAIT_FOR_FORKED_PROCESS_WITHOUT_LOOPING == 0) \
    { \
        while (true) \
        { \
            result = waitpid(child_pid, &child_return, WNOHANG); \
			if (result == child_pid) \
			{ \
				break; \
			} \
			if (time(NULL) - start_time > TIMEOUT_SECONDS) \
			{ \
				kill(child_pid, SIGKILL); \
				TEST_FAIL_MESSAGE("The " #function_name " function took too long to execute."); \
			} \
                usleep(SLEEP_MICROSECONDS); \
		} \
    } \
    else \
    { \
		result = waitpid(child_pid, &child_return, 0); \
    } \
} while (!WIFEXITED(child_return) && (errno == EINTR)); \
if (WEXITSTATUS(child_return) == EXIT_TEST_FAILED) \
{ \
    Unity.CurrentTestFailed = 1; \
    TEST_ABORT(); \
} \
else if (WEXITSTATUS(child_return) == EXIT_UNEXPECTED_RETURN_VALUE) \
{ \
	TEST_FAIL_MESSAGE("The " #function_name " function did not return the expected value."); \
} \
else if (WEXITSTATUS(child_return) == EXIT_NOT_IMPLEMENTED) \
{ \
    not_implemented_##function_name = true; \
    TEST_FAIL_MESSAGE("The " #function_name " function has not been implemented."); \
} \
else if (WEXITSTATUS(child_return) == EXIT_SHM_FAILED) \
{ \
    TEST_FAIL_MESSAGE("Shared memory could not be set up when testing the " #function_name " function."); \
} \
else if (WEXITSTATUS(child_return) == EXIT_MALLOC_FAILED) \
{ \
    TEST_FAIL_MESSAGE("Memory could not be allocated when testing the " #function_name " function."); \
} \
else if (WEXITSTATUS(child_return) == EXIT_FORK_FAILED) \
{ \
	TEST_FAIL_MESSAGE("Could not fork child process when testing the " #function_name " function."); \
} \
else if (WEXITSTATUS(child_return) == EXIT_UNRELATED_FAILURE) \
{ \
    TEST_FAIL_MESSAGE("There was a failure testing the " #function_name " function, but it was not caused by the function itself."); \
} \
else if (WEXITSTATUS(child_return) == EXIT_UNEXPECTED_NULL) \
{ \
    TEST_FAIL_MESSAGE("A NULL value was unexpectedly returned when testing the " #function_name " function."); \
} \
else if (child_return != 0) \
{ \
    crashes_##function_name = true; \
    TEST_FAIL_MESSAGE("The " #function_name " function or one of the functions it called crashed or encountered an irrecoverable error."); \
} \

/**
 * @brief Macro for waiting for all children to finish, returning the value from the specific child PID
 */
#define WAIT_FOR_CHILDREN(function_name) \
int child_return = 0; \
char* error_message = NULL; \
bool test_failed = false; \
\
do \
{ \
    pid_t child_pid; \
	child_pid = wait(&child_return); \
    child_pid = child_pid; \
	\
    if (WEXITSTATUS(child_return) == EXIT_TEST_FAILED) \
    { \
        Unity.CurrentTestFailed = 1; \
        TEST_ABORT(); \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_UNEXPECTED_RETURN_VALUE) \
    { \
	    error_message = "The " #function_name " function did not return the expected value."; \
        test_failed = true; \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_NOT_IMPLEMENTED) \
    { \
        not_implemented_##function_name = true; \
        error_message = "The " #function_name " function has not been implemented."; \
        test_failed = true; \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_SHM_FAILED) \
    { \
        error_message = "Shared memory could not be set up when testing the " #function_name " function."; \
        test_failed = true; \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_MALLOC_FAILED) \
    { \
        error_message = "Memory could not be allocated when testing the " #function_name " function."; \
        test_failed = true; \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_FORK_FAILED) \
    { \
	    error_message = "Could not fork child process when testing the " #function_name " function."; \
        test_failed = true; \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_UNRELATED_FAILURE) \
    { \
        error_message = "There was a failure testing the " #function_name " function, but it was not caused by the function itself."; \
        test_failed = true; \
    } \
    else if (WEXITSTATUS(child_return) == EXIT_UNEXPECTED_NULL) \
    { \
        error_message = "A NULL value was unexpectedly returned when testing the " #function_name " function."; \
	    test_failed = true; \
    } \
    else if (child_return != 0) \
    { \
        crashes_##function_name = true; \
        error_message = "The " #function_name " function or one of the functions it called crashed or encountered an irrecoverable error."; \
        test_failed = true; \
    } \
} while (child_pid > 0 || (!WIFEXITED(child_return) && (errno == EINTR))); \
\
if (test_failed) \
{ \
	TEST_FAIL_MESSAGE(error_message); \
}

/**
 * @brief Macro for saving the existing abort frame for returning to when there is an error
 */
#define TEST_SAVE_ABORT_FRAME() \
jmp_buf original_abort_frame; \
do \
{ \
    memcpy(original_abort_frame, Unity.AbortFrame, sizeof(jmp_buf)); \
} \
while(0)

/**
 * @brief Macro for restoring the original abort frame for returning to when there is an error
 */
#define TEST_RESTORE_ABORT_FRAME() \
do \
{ \
    memcpy(Unity.AbortFrame, original_abort_frame, sizeof(jmp_buf)); \
} \
while(0)

/**
 * @brief Macro for retrying in the case of intermittent failures
 */
#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY(expression) \
  (__extension__							      \
    ({ long int __result;						      \
       do __result = (long int) (expression);				      \
       while (__result == -1L && errno == EINTR);			      \
       __result; }))
#endif

/**
 * @brief Macro for retrying in the case of intermittent failures
 */
#ifndef TEMP_FAILURE_RETRY_WITH_LIMITS
#define TEMP_FAILURE_RETRY_WITH_LIMITS(expression) \
(__extension__                                  \
 ({ long int __result; int __run_count = 0;                              \
    do { __result = (long int) (expression); }                     \
     while (__run_count++ < 1 && __result == -1L && errno == EINTR);                  \
     __result; }))
#endif

/**
 * @brief Add ^ and $ anchors to a regex pattern so it spans the full string
 * @param pattern Pattern to add anchors to
 * @return Pattern with anchors
 */
char* add_regex_anchors(const char* pattern);

/**
 * @brief Determines if the string is equal to the regex pattern
 * @param pattern Pattern to test
 * @param string String to check
 * @return True if the string is equal to the pattern, false otherwise
 */
bool are_equals_regex(const char* pattern, const char* string);

/**
 * @brief Builds a full path from directory and file names
 * @param directory Directory path to use
 * @param filename Filename to use
 * @return Full path
 */
char* build_path(const char* directory, const char* filename);

/**
 * @brief Cleans newlines in a string by replacing \r\n with \n
 * @param input String to be cleaned
 * @return String with all \n newlines
 */
char* clean_newlines(const char* input);

/**
 * @brief Cleans a string using specified options
 * @param input String to be cleaned
 * @param text_matching_options Options to use in cleaning string
 * @return Cleaned string
 */
char* clean_string(const char* input, enum text_matching text_matching_options);

/**
 * @brief Gets number of bytes malloced for a pointer
 * @param ptr Pointer to check
 * @return Number of bytes
 */
size_t ctest_get_malloc_size(void* ptr);

/**
 * @brief Determines if a file exists
 * @param path File to check
 * @return True if it exists, false otherwise
 */
bool does_file_exist(const char* path);

/**
 * @brief Determines if the file contains the specified regex pattern
 * @param pattern Pattern to test
 * @param path File to check
 * @return True if the file contains the pattern, false otherwise
 */
bool file_contains_regex(const char* pattern, const char* path);

/**
 * @brief Gets captured output
 * @return Captured outpout or NULL if there was none
 */
char* get_captured_output(void);

/**
 * @brief Get the directory part of a path
 * @param path Path to extract directory from
 * @return Directory part of path
 */
char* get_directory(const char* path);

/**
 * @brief Get the size of a file
 * @param path File to check
 * @return Size of file
 */
size_t get_file_size(const char* path);

/**
 * @brief Determines if the string contains the specified regex pattern
 * @param pattern Pattern to test
 * @param string String to check
 * @return True if the string contains the pattern, false otherwise
 */
bool is_contained_regex(const char* pattern, const char* string);

/**
 * @brief Duplicates a string
 * @param string String to be duplicated
 * @return Duplicate of string
 */
char* duplicate_string(const char* string);

/**
 * @brief Reads contents of a file
 * @param path Path to file
 * @return Contents of file
 */
char* read_file(const char* path);

/**
 * @brief Reads contents of a file in the same directory as source code file
 * @param filename file to open
 * @return Contents of file
 */
char* read_source_code_file(const char* filename);

/**
 * @brief Writes a string to a file
 * @param path Path to write to
 * @param contents String to write to file
 * @param overwrite If true, overwrites file if it exists
 * @return Contents of existing file if it exists, NULL otherwise
 */
char* write_file(const char* path, const char* contents, bool overwrite);