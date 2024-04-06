This project we are tasked with using semaphores and shared memory to sync the producer and consumer problem.

The requirements are there must be a table with size 2 elements, a producer will put items on the table
and the consumer will take items off the table and consume them. The producer and consumer are in different 
proccesses therefore semaphores and shared memory must be used to sync them. 

Here is how to run the code.

  1. Go into a unix based terminal
  2. enter the following into the command line

      $ gcc producer.c -pthread -lrt -o producer
      $ gcc consumer.c -pthread -lrt -o consumer
      $ ./producer & ./consumer &


The comand line will then show the results of the code running.
