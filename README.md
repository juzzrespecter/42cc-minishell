# minishell
  
  
[ Made by [@danrodri](https://profile.intra.42.fr/users/danrodri/), [@fgomez-s](https://profile.intra.42.fr/users/fgomez-s) ]  
</br>
_Part of 42 common core cursus; develop a simple shell program based on bash behavior and syntax._  
</br></br>
This project aims to introduce students to processes and file descriptor management, how they work and their meaning in behind their user interface [ how Kernel manages resources in different processes, how can processes communicate with each other, why [everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file) in Linux and how can we interact as programmers with all of this ].  
  
With these points on mind, we implemented a little shell, having __bash__ as a reference, that will allow us to work with system calls such as   [ __execve__, __fork__, __wait__, __dup__, __pipe__ ], and work with processes and fd in our code in a lower, more interesting level.  
  
  
## List of implemented shell features
### Quoting
Shell must parse its input paying mind to double quotes [ allowing env. variables expansion ], simple quotes [ literal processing of text ], and escaped characters, and every possible interaction between the three of them.  
Multiline processing is not present at this moment.  
  
### History & line edit management
The minishell must handle an history file that can be accesed and interacted with, using the [ __termcap__ ] library to interact with the working terminal.  
User input in prompt can, also, be edited cleanly.  
  
### Builtins:
The following builtins from bash are replicated and present in this project:  
  
 *  **[ echo ]**  
   Print to standard output passed parameters, flag __[ -n ]__ implemented.  
 *  **[ cd ]**  
   Change directory builting, works only with relative or absolute path.  
 *  **[ pwd ]**  
   Print working directory, no options.  
 *  **[ export ]**  
   Export enviroment variables, no options.  
 *  **[ unset ]**  
   Unset enviroment variables, no options.  
 *  **[ env ]**  
   Show enviroment variables present on shell, no options, no arguments.  
 *  **[ exit ]**  
   Exit process with argument as exit code, no options.  

### Environment variables
Minishell inherits environment variables from parent shell, and is capable of managing variable interaction from user; variables can be accessed and expanded as in bash [ using $ followed by var. name ], new variables can be created and exported, and also be edited and removed from the environment.  
  
### Pipelines
Like bash, commands can be piped in minishell. Standard input and output will be managed to communicate the child processes in the pipeline.  
  
### Redirections
The following input and output redirections are implemented: __[ '>', '<', '>>' ]__.  
They work as expected in bash, single closing angle bracket overwrittes if must the resulting file, whereas double closing angle bracket will try to append if output file already exists.  
Heredoc operator is currently not implemented.  
File descriptor aggregation is currently not implemented.  
  
### Signal handling from user input
Minishell can handle three signal inputs from user in three different contexts:  
* __[ ctrl-C ]__ will jump to a new line and print a new prompt with and without user input, and will work as expected when minishell is waiting for a child process to end [ usually throwing a SIGINT ].  
* __[ ctrl-D ]__ will end the process if prompt is empty, will be ignored with user input and work as expected with an active child process.  
* __[ ctrl-\ ]__  will be ignored whether line has user input or not, will work as expected while waiting for a child process [ usually SIGQUIT ].  

## Usage
```
make && ./minishell
```


_> Project passed with [100/100] mark ✅😎 <_
