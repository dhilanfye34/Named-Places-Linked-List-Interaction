# Named Places Linked List Interaction

This project implements a linked list structure to manage and interact with data about various named places across the United States. The program reads data from a file, processes it into a linked list, and provides functionality to search for places by name or by both name and state.

## Features

- **Dynamic Linked List Management**:
  - Create and insert nodes representing places.
  - Search for places by name or by a combination of name and state.

- **File Input**:
  - Reads place data from a formatted text file.
  - Parses fields such as code, state abbreviation, name, population, area, latitude, longitude, road ID, and distance.

- **Interactive User Interface**:
  - Allows users to search for places by name.
  - Provides detailed information about places when matched.
  - Handles errors and prompts for retry when invalid inputs are provided.

## File Format

The input file (`np.txt`) must have data organized with the following fields:
1. `Code` - Unique identifier for the place.
2. `State` - Two-character abbreviation of the state.
3. `Name` - Name of the place (up to 45 characters).
4. `Population` - Number of residents in the place.
5. `Area` - Geographic area in square miles.
6. `Latitude` and `Longitude` - Coordinates of the place.
7. `Road ID` - Identifier for a road associated with the place.
8. `Distance` - Distance to the next significant location.

Example line:
64200100 PAAaronsburg 485 0.520877 40.900946 -77.453383 7795 7.6972


## Functions

### Core Functionalities
1. **`create_place`**:
   - Creates a new place node with the provided data.
2. **`insert_place`**:
   - Inserts a new place node into the linked list.
3. **`read_places`**:
   - Reads data from a file, parses it, and constructs the linked list.
4. **`search_name`**:
   - Searches the linked list for places matching a given name.
5. **`search_name_and_state`**:
   - Searches for a place by both name and state abbreviation.
6. **`print`**:
   - Displays detailed information about a place.

### Helper Functions
- **`trim`**:
  - Trims trailing spaces from strings.

## How to Run

1. Compile the program using a C compiler:
   ```bash
   gcc -o places linked_list.c
