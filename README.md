The LZW program writen in C encodes sequences of 8-bit data. The codes from 0 to 255 represent 1-character sequences 
consisting of the corresponding 8-bit character, and the codes 256 through 4095 are created in a dictionary for 
sequences encountered in the data as it is encoded. At each stage in compression, input bytes are gathered into a 
sequence until the next character would make a sequence for which there is no code yet in the dictionary. 
The code for the sequence (without that character) is added to the output, 
and a new code (for the sequence with that character) is added to the dictionary.
