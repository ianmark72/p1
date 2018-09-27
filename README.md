   This program is a simplified version of the ps command. Based on the users imput the program will search through the /proc directory and either print information about one specific process or every process owned by the user.

        First we created booleans of all information arguments and set them to what they defaulted to. From there we parsed through the arguments with getopt() and a switch statement. Within the switch statement we changed the booleans if neccessary. From there we called a method name getInfo() with the booleans and the pid as the arguments.

        In getInfo() we determine if a specific process should be accessed or all. If only one we called the helper functions if the information was needed. The helper function were methods in separate files that simply took the pid and found the needed information and concatenated the information on to a final string.
