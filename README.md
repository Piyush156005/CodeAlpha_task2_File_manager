# CodeAlpha_task2_File_manager
this is a file manager made in c++ 
All the files are made in same directory in which the task2.cc code is saved.
All functions of the code
1.ls: List Files

  Lists all files and directories in the current directory.
  Displays directories with a [D] prefix and files with a [F] prefix.
  Skips entries that start with a dot (.), which typically represent hidden files.
  
2.mkdir <directory_name>: Create Directory

  Creates a new directory with the specified name in the current directory.
  Displays a success message if the directory is created successfully; otherwise, it shows an error.
  
3.cp <source> <destination>: Copy File

  Copies a file from the source path to the destination path within the current directory.
  Reads the source file in binary mode and writes to the destination file.
  Displays a message indicating the result of the copy operation.
  
4.mv <source> <destination>: Move (or Rename) File

  Moves a file from the source path to the destination path within the current directory.
  If the destination file already exists, prompts the user for confirmation to overwrite it.
  Displays a message indicating the result of the move operation.
  
5.cd <directory_name>: Change Directory

  Changes the current working directory to the specified directory.
  Updates the currentPath variable to reflect the new working directory.
  Displays an error message if the specified directory does not exist.
  
6.exit: Exit the Program
  Terminates the program and exits the command loop.
