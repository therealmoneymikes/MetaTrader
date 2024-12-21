//Notes for PostGreSQL Library
// For
//Install the postgreSQL Server Dev package
//if you are on windows go to the

<!-- For Windows Users -->
<!-- POWERSHELL COMMAND TO FIND LIBPQ-FE.H -->

COMMAND = Get-ChildItem -Path "C:\Program Files\PostgreSQL" -Recurse -Filter "libpq-fe.h" -ErrorAction SilentlyContinue

To get access to the <libpq-fe.h> header file

1. Install PostgreSQL
2. Add PostgreSQL bin directory to PATH
   //Path should be : C:\Program Files\PostgreSQL\xx\bin xx = Version you've installed
3. If you do not have the C++ compiler and toolchains you can get them here https://visualstudio.microsoft.com/downloads/
4. Just like how we have Include files in MQL4 and MQL5 the libpq-fe.h is located in the e.g for postgreSQL16 postgreSQL/16/include folder
5. Add directory link along with the name of header to use it for the dll file,
   Link the file to the library path for compling/

   <!-- PLEASE USE -I to tell the compiler that path to an include dir -->
   <!-- If you are using a library use -L -->
   <!-- Because we are using the libpq library add -lpq -->

The best practice is to set environmental variables that represent
the include folder and library folder to do this add

For temporary Environmental Variables for the Include and Library paths, write this
into the terminal. Write these:
set CPPFLAGS=-I"C:\Program Files\PostgreSQL\<version>\include"
set LDFLAGS=-L"C:\Program Files\PostgreSQL\<version>\lib"

These will as long as you can keep the same terminal open

For a more permanent solution set CPPFLAGS and LDFLAGS in the system environmental
variable, add them under the System Variables Section

Then when you build the project for example with g++ you can reference
them using the % syntax as follows:

g++ %CPPFLAGS% %LDFLAGS% -lpq postgredb.cpp -o your_program_name

export CPPFLAGS="-

<!-- For MAC and link users  -->

Follow Steps 1-3 from the Windows install

4. Use Finder to help you search for the postgreSQL folder.
   The include files show me location in the path structure of:

/usr/local/opt/libpq/include
Use the find keyword in your termnical to get and confirm the location of the header file with this command:

find /<your username>/local/ -name "libpq-fe.h"

5. To store the CPPFLAGS and LDFLAGS as environmental variables

I recommend you store them in .bashrc files (cd to ~/.bashrc)
Or with zsh using .zshrc (cd to ~/.zshrc)

Then add:

export CPPFLAGS="-I/usr/local/opt/libpq/include"
export LDFLAGS="-L/usr/local/opt/libpq/lib"

if you want the temporal equivalent like the windows set then
use same flag variables in your current terminal e.g vscode

export CPPFLAGS="-I/usr/local/opt/libpq/include"
export LDFLAGS="-L/usr/local/opt/libpq/lib"

<!-- I have template CMake file for cross platform intergration if you like to use
it for more complexed operations or to build the dll fill by itself you can use it ;)
