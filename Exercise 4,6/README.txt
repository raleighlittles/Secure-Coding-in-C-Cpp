The purpose of the first part this exercise is to identify some
common memory management errors and gain familiarity with the
Valgrind memory checking tool using a realistic program.

A Caesar cipher, also known as a shift cipher, is one of the simplest
and most widely known encryption techniques. It is a type of
substitution cipher in which each letter in the plaintext is replaced
by a letter some fixed number of positions down the alphabet. For
example, with a shift of 3, A would be replaced by D, B would become
E, and so on.  The method is named after Julius Caesar, who used
it to communicate with his generals.

NOTE: this cipher must NEVER be used in a real application.  It is
trivially broken using either a brute-force attack or statistical
analysis of letter frequency in the ciphertext.  It is NOT an
acceptable form of cryptography and in practice offers essentially
no communication security.  It is only used here to simulate a
security-sensitive operation.

The supplied program, caesar.c, decrypts the messages, one per line,
in the file encrypted.txt using the "keys" stored in the keys.txt
file.  The decrypted output (which we want to keep from prying eyes)
is printed to an output file if one is specified or stdout if not.

Compile the sample program as follows:

$ cc -g3 -o caesar caesar.c

You should assume this program will be running in an environment
where the keys file and decrypted results file are not intended to
be read by unauthorized users (file permissons 400 or 600) in order
to protect sensitive information.
