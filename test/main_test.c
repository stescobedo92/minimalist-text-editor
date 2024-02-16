#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define MAX_BUFFER_SIZE 1024

void edit_line(char* buffer, int current_line) {
    for(int i=0; i < current_line; i++) {
        buffer = strchr(buffer, '\n') + 1;
    }

    char* line_end = strchr(buffer, '\n');
    char saved[1024] = {0};
    strcpy(saved, line_end);
    scanf("%s", buffer);
    strcpy(buffer + strlen(buffer), saved);
}

void read_file_content(const char* filename, char* buffer) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    fread(buffer, MAX_BUFFER_SIZE, 1, file);
    fclose(file);
}

void write_file_content(const char* filename, const char* buffer) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    fwrite(buffer, strlen(buffer), 1, file);
    fclose(file);
}

// Test suite initialization function
int init_suite(void) {
    return 0;
}

// Test suite cleanup function
int clean_suite(void) {
    return 0;
}

// Test for edit_line function
void test_edit_line(void) {
    char buffer[MAX_BUFFER_SIZE] = "Line 1\nNew line 2\nText 1\n";
    read_file_content("test_input_1.txt", buffer);
    edit_line(buffer, 2);
    CU_ASSERT_STRING_EQUAL(buffer, "Line 1\nNew line 2\nText 1\n");
}

// Test for read_file_content function
void test_read_file_content(void) {
    char buffer[MAX_BUFFER_SIZE];
    read_file_content("test_input.txt", buffer);
    CU_ASSERT_STRING_EQUAL(buffer, "Test content\n");
}

// Test for write_file_content function
void test_write_file_content(void) {
    char buffer[MAX_BUFFER_SIZE] = "Test content\n";
    write_file_content("test_output.txt", buffer);

    // Check if the file was written correctly by reading it again
    char read_buffer[MAX_BUFFER_SIZE];
    read_file_content("test_output.txt", read_buffer);
    CU_ASSERT_STRING_EQUAL(buffer, read_buffer);
}

int main() {
    CU_pSuite pSuite = NULL;

    // Initialize the test log
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Add a test suite to the registry
    pSuite = CU_add_suite("Test Suite", init_suite, clean_suite);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if (CU_add_test(pSuite, "Test for edit_line function", test_edit_line) == NULL ||
        CU_add_test(pSuite, "Test for read_file_content", test_read_file_content) == NULL ||
        CU_add_test(pSuite, "Test for write_file_content", test_write_file_content) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using basic mode
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clear the test log
    CU_cleanup_registry();

    return CU_get_error();
}