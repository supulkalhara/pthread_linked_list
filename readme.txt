Running the serial program

    Compile the serial.c and linkedList.c into an executable file
    Run the executable with the following command line arguments in order
        n, m, m_member, m_insert, m_delete, results_filename
        Ex: ./serial 1000 10000 0.9 0.05 0.05 results.txt 
    The time taken will be printed to the terminal


Running the the One Mutex and ReadWrite Lock program

    Compile the required file with LinkedList.c
    Run the executable with the following command line arguments in order
        number of threads, n, m, m_member, m_insert, m_delete, results_filename
        Ex: ./serial 4 1000 10000 0.9 0.05 0.05 results.txt 
    The time taken will be printed to the terminal


Running the complete tests

    For serial, run run_test_serial.sh script
    It will run and store the results of the test 385 num_times

    For Mutex and ReadWrite locks, run run_test.sh script
    It will run 385 tests for each number of threads and each type of solution

    The case parameters (n, m, m_member etc) has to be specified in the script file. 