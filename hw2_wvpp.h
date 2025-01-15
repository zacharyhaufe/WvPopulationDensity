/**
 * @file hw2_wvpp.h
 * @brief Header file for CS 350 Homework #2: West Virginia Population Problem
 * @author Brian Powell
 * @version 3.7
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

#pragma once

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

/**
 * @brief Struct for a linked list
*/
struct list {
	/**
	 * @brief Pointer to head node of linked list
	*/
	struct node* headPtr;
};

/**
 * @brief Function to return the name of the programmer
 * @return String with the name of the programmer
 */
const char* get_programmer_name(void);

/**
 * @brief Removes whitespace from the leading and trailing ends of a string
 * @param untrimmed String to remove whitespace from
 * @return New string with whitespace removed
 */
char* trim(const char* untrimmed);

/**
 * @brief Returns substring of original string
 * @param source String to take substring from
 * @param start_index Starting index for substring (character is included in result)
 * @param end_index Ending index for substring (substring ends at character immediately before this index)
 * @return New string containing substring
 */
char* substring(const char* source, unsigned int start_index, unsigned int end_index);

/**
 * @brief Creates a new linked list
 * @return Pointer to new list
*/
struct list* create_list(void);

/**
 * @brief Get the head node for a linked list
 * @param listPtr Linked list to get head node for
 * @return Head node for linked list, or NULL if list is empty
*/
struct node* get_head_node(struct list* listPtr);

/**
 * @brief Get county name from specified node
 * @param nodePtr Node to get county name from
 * @return Name of county
*/
const char* get_county_name(struct node* nodePtr);

/**
 * @brief Get FIPS Code from specified node
 * @param nodePtr Node to get FIPS Code from
 * @return FIPS Code, or NULL if node is invalid
*/
const char* get_fips_code(struct node* nodePtr);

/**
 * @brief Get seat from specified node
 * @param nodePtr Node to get seat from
 * @return Seat, or NULL if node is invalid
*/
const char* get_seat(struct node* nodePtr);

/**
 * @brief Get population from specified node
 * @param nodePtr Node to get population from
 * @return Population, or -999 if node is invalid
*/
int get_population(struct node* nodePtr);

/**
 * @brief Get area from specified node
 * @param nodePtr Node to get area from
 * @return Area, or -999 if node is invalid
*/
int get_area(struct node* nodePtr);

/**
 * @brief Get populationd density (population/area) for specified node
 * @param nodePtr Node to get population density for
 * @return Number of people per square mile, or -999 if node is invalid
*/
double get_population_density(struct node* nodePtr);

/**
 * @brief Get next node for specified node
 * @param nodePtr Node to get next node for
 * @return Next node, or NULL if there are no more nodes in the linked list
*/
struct node* get_next_node(struct node* nodePtr);

/**
 * @brief Create new node to represent a county
 * @param county_name Name of county
 * @param fips_code FIPS Code
 * @param seat Seat of county
 * @param population Population of county
 * @param area Area of county in square miles
 * @return New node loaded with data for the county
*/
struct node* create_county(const char* county_name, const char* fips_code, const char* seat, int population, int area);

/**
 * @brief Add new county node to list, leaving list sorted in descending order by population density
 * @param listPtr Linked list to add county to
 * @param nodePtr Node containing county data
*/
void add_and_sort_county(struct list* listPtr, struct node* nodePtr);

/**
 * @brief Process a line of data from input file
 * @param data Line of data to process
 * @return New node storing data from the line
 */
struct node* process_input_line(const char* data);

/**
 * @brief Load counties from file, storing them each as nodes in linked list
 * @param listPtr Linked list to store counties in as nodes
 * @param filename name of fixed-width column text file to load counties from
*/
void load_counties(struct list* listPtr, const char* filename);

/**
 * @brief Delete node from list by its county name
 * @param listPtr Linked lst to delete from
 * @param county_name Name of county for node to be deleted
 * @return 0 if successfully deleted, 1 if county did not exist
*/
int delete_by_county_name(struct list* listPtr, const char* county_name);

/**
 * @brief Save counties from linked list to CSV file
 * @param listPtr linked list containing counties to be saved
 * @param filename CSV file to save counties in
*/
void save_counties(struct list* listPtr, const char* filename);