/**
 Zachary Haufe
 hw2_wvpp.c
 File containing code that investigates figures related to population density across West Virginia
 */

// Include statements
#include "hw2_wvpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node struct
typedef struct node
{
    char county_name[100];
    char fips_code[100];
    char seat[100];
    int population;
    int area;
    
    struct node* next; // Pointer to the next node in the list
} Node;

const char* get_programmer_name(void)
{
    return "Zachary Haufe";
}

char* trim(const char* untrimmed)
{
    if (untrimmed == NULL)
    {
        return NULL; // Return NULL if untrimmed is NULL
    }
    
    // Find the length of the string
    size_t length = strlen(untrimmed);
    
    // Find the start of the string
    const char* start = untrimmed;
    while (*start && isspace((unsigned char)*start)) // Loop to exclude whitespace in the start of the string
    {
        start++;
    }

    // If the string is all whitespace, return empty string.
    if (*start == '\0')
    {
        char* emptyStr = (char*)malloc(1);
        if (emptyStr == NULL)
        {
            return NULL;
        }
        emptyStr[0] = '\0';
        return emptyStr;
    }
    
    // Find the end of the trimmed string
    const char* end = untrimmed + length - 1;
    while (end > start && isspace((unsigned char)*end)) // Loop to exclude whitespace
    {
        end--;
    }

    // Calculate the length of the trimmed string
    size_t trimmedLength = end - start + 1;

    // Allocate memory for the new trimmed string
    char* trimmed = (char*)malloc(trimmedLength + 1);
    if (trimmed == NULL)
    {
        return NULL; // Returning NULL if memory cannot be allocated
    }

    // Copy the trimmed content and null-terminate the string
    strncpy(trimmed, start, trimmedLength);
    trimmed[trimmedLength] = '\0';

    return trimmed;
    }


char* substring(const char* source, unsigned int start_index, unsigned int end_index)
{
    if (source == NULL)
    {
        return NULL; // Return NULL if source is NULL
    }
    
    // Get the length of the source string
    size_t source_length = strlen(source);

    // Check if start_index and end_index are valid
    if (start_index > source_length || end_index > source_length || start_index > end_index)
    {
        return NULL;
    }

    // Calculate the length of the substring
    size_t substring_length = end_index - start_index;

    // Allocate memory for the new substring (including space for null terminator)
    char* substring = (char*)malloc(substring_length + 1);
    if (substring == NULL)
    {
        return NULL; // Return NULL if memory cannot be allocated
    }

    // Copy the substring from the source
    strncpy(substring, source + start_index, substring_length);

    // Null-terminate the substring
    substring[substring_length] = '\0';
    
    return substring;
}

struct list* create_list(void)
{
    // Allocate memory for the new list
    struct list* new_list = (struct list*)malloc(sizeof(struct list));
    if (new_list == NULL)
    {
        return NULL; // Return NULL if memory cannot be allocated
    }

    // Initialize the head pointer
    new_list->headPtr = NULL;

    // Return a pointer to the new list
    return new_list;
}

struct node* get_head_node(struct list* listPtr)
{
    // Check if the provided list is NULL
    if (listPtr == NULL)
    {
        return NULL;
    }

    // Return a pointer to the head node
    return listPtr->headPtr;
}

const char* get_county_name(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return NULL;
    }

    // Return the county name from the specified node
    return nodePtr->county_name;
}

const char* get_fips_code(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return NULL;
    }

    // Return the FIPS code from the specified node
    return nodePtr->fips_code;
}


const char* get_seat(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return NULL;
    }

    // Return the seat from the specified node
    return nodePtr->seat;
}

int get_population(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return -1; // -1 indicates NULL
    }

    // Return the population from the specified node
    return nodePtr->population;
}

int get_area(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return -1; // -1 indicates NULL
    }

    // Return the area from the specified node
    return nodePtr->area;
}

double get_population_density(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return -1.0; // -1.0 indicates NULL
    }
    
    // Check if the area is non-zero to avoid division by zero
    if (nodePtr->area <= 0)
    {
        return -1.0;
    }
    
    // Calculate population density
    double population_density = (double)nodePtr->population / nodePtr->area;
    return population_density;
}
   
struct node* get_next_node(struct node* nodePtr)
{
    // Check if the provided node is NULL
    if (nodePtr == NULL)
    {
        return NULL;
    }

    // Return the pointer to the next node
    return nodePtr->next;
}
    
struct node* create_county(const char* county_name, const char* fips_code, const char* seat, int population, int area)
{
    // Check if any of the string parameters are NULL
    if (county_name == NULL || fips_code == NULL || seat == NULL)
    {
        return NULL;
    }

    // Dynamically allocate memory for a new node
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Initialize the members of the node with provided arguments
    strncpy(new_node->county_name, county_name, sizeof(new_node->county_name) - 1);
    new_node->county_name[sizeof(new_node->county_name) - 1] = '\0'; // Ensure null termination

    strncpy(new_node->fips_code, fips_code, sizeof(new_node->fips_code) - 1);
    new_node->fips_code[sizeof(new_node->fips_code) - 1] = '\0'; // Ensure null termination

    strncpy(new_node->seat, seat, sizeof(new_node->seat) - 1);
    new_node->seat[sizeof(new_node->seat) - 1] = '\0'; // Ensure null termination

    new_node->population = population;
    new_node->area = area;
    new_node->next = NULL; // Initialize the next pointer to NULL

    // Return the newly created node
    return new_node;
}

void add_and_sort_county(struct list* listPtr, struct node* nodePtr)
{
    if (listPtr == NULL || nodePtr == NULL)
    {
        return; // Return if the provided list or node is NULL
    }

    // Calculate the population density of the new node
    double new_node_density = get_population_density(nodePtr);

    // If the list is empty or the new node's density is greater than the head's density, insert at the head
    if (listPtr->headPtr == NULL || new_node_density > get_population_density(listPtr->headPtr))
    {
        nodePtr->next = listPtr->headPtr;
        listPtr->headPtr = nodePtr;
        return;
    }

    // Traverse the list to find the appropriate position to insert the new node
    struct node* current = listPtr->headPtr;
    while (current->next != NULL && get_population_density(current->next) >= new_node_density)
    {
        current = current->next;
    }

    // Insert the new node at the correct position
    nodePtr->next = current->next;
    current->next = nodePtr;
}

struct node* process_input_line(const char* data)
{
    if (data == NULL)
    {
       return NULL; // Return NULL if data is NULL
    }
    // Extract and trim each field using fixed-width substrings
    char* county_name = trim(substring(data, 0, 16));
    char* fips_code = trim(substring(data, 16, 19));
    char* seat = trim(substring(data, 19, 44));
    char* population_str = trim(substring(data, 44, 56));
    char* area_str = trim(substring(data, 56, 64));

    // If any fields are NULL, free allocated memory and return null
    if (!county_name || !fips_code || !seat || !population_str || !area_str)
    {
        free(county_name);
        free(fips_code);
        free(seat);
        free(population_str);
        free(area_str);
        return NULL;
    }

    // Convert data types for population and area
    int population = atoi(population_str);
    int area = atoi(area_str);

    // Free the previous types
    free(population_str);
    free(area_str);

    // Create new node with extracted data
    struct node* new_node = create_county(county_name, fips_code, seat, population, area);

    free(county_name);
    free(fips_code);
    free(seat);

    return new_node;
}

void load_counties(struct list* listPtr, const char* filename)
{
// Check if the provided list is NULL
    if (listPtr == NULL)
    {
        return; // Exit without doing anything
    }

    // Open the text file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return; // Exit without doing anything if the file cannot be opened
    }
        char buffer[256];

        // Ignore the first row (header) in the file
        if (fgets(buffer, sizeof(buffer), file) == NULL)
        {
            fclose(file);
            return; // Exit if unable to read the first line
        }

        // Process each subsequent line
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            // Trim any trailing newline characters from the buffer
            buffer[strcspn(buffer, "\n")] = '\0';

            // Process the data line and create a new node
            struct node* new_node = process_input_line(buffer);
            if (new_node != NULL) {
                // Add the node to the list, sorted by population density
                add_and_sort_county(listPtr, new_node);
            }
        }

        // Close the file after processing
        fclose(file);
}

int delete_by_county_name(struct list* listPtr, const char* county_name)
{
    // Check if the provided list is NULL
    if (listPtr == NULL)
    {
        return 2; // Indicate the list is NULL
    }

    // Check if the list is empty
    struct node* current = listPtr->headPtr;
    struct node* previous = NULL;

    // Traverse the list to find the node with the specified county name
    while (current != NULL)
    {
        if (strcmp(current->county_name, county_name) == 0)
        {
            // Hit, node found, remove it from the list
            if (previous == NULL)
            {
                // The node to be removed is the head of the list
                listPtr->headPtr = current->next;
            }
            else
            {
                // The node to be removed is not the head
                previous->next = current->next;
            }
            // Free the memory allocated for the node
            
           // free(current->county_name);
        
            free(current);
            return 0; // Indicate success
        }
        // Move to the next node
        previous = current;
        current = current->next;
    }

    // Miss, node not found
    return 1;
}

void save_counties(struct list* listPtr, const char* filename)
{
    // Check if the provided list is NULL
    if (listPtr == NULL)
    {
    return; // Do nothing
    }

    // Open the file for writing
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        return; // Do nothing
    }

    // Write the header row to the file
    fprintf(file, "County Name,FIPS Code,Seat,Population,Area,Population Density\n");

    // Traverse the list and write each county's data
    struct node* current = listPtr->headPtr;
    while (current != NULL)
    {
        
        // Calculate population density
        double population_density = get_population_density(current);

        // Write county data
        fprintf(file, "%s,%s,%s,%d,%d,%.2f\n",
                current->county_name,
                current->fips_code,
                current->seat,
                current->population,
                current->area,
                population_density);

        // Move to the next node
        current = current->next;
    }

    // Close the file
    fclose(file);
}
