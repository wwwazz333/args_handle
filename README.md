# handle_args

## Usage

`handle_args` is a function that will hanlde your args passed to the program in order.

Used like this `handle(argc, argv, function_that_handle_an_arg);`

Your `function_that_handle_an_arg` must look like this.

```C
void function_that_handle_an_arg(char* str_action, char* str_params){
	printf("Action : %s\n", str_action);
	printf("Params : %s\n\n", str_params);
}
```

Example of output for `./main -Da --name "A name" --file file123 p_default -g`

```bash
Action : D
Params : (Null)

Action : a
Params : (Null)

Action : name
Params : A name

Action : file
Params : file123

Action : (Null)
Params : p_default

Action : g
Params : (Null)
```

## Installation

### With code source

You can directly download `handle_args.c` and `handle_args.h` to use them in your code.

### Linux download

clone this repo and open it 

`git clone https://github.com/wwwazz333/handle_args.git && cd handle_args`

run `sudo make install`

use it in other of your project
```c
#include <handle_args.h>
```

compile withe `-lhandle_args`

for example

```bash
gcc main.c -o main -lhandle_args
```

### Static library

`make static`

### Dynamic library

`make dynamic`