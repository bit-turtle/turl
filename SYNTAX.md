# Turl Syntax
- Style:
  - Lines are separated by newlines and by ';'
  - Quotes can be put on everything
  - There can be lots of whitespace

Turl Instructions:
- `delete (number/string) **name** ...`
  - Frees the program namespace of variable names and deletes the values of the variables
  - Example
  - `delete string a`
- `create (number/string) **name** {typemath}`
  - Creates a variable of a specific type
  - Example:
    - `create number "# of cats in world" = 2000000`
- `(number/string) **name** {typemath}`
Those two commands create or get variables before doing typemath on them
## What is typemath
Type math is how you do math on variables and how you set them
Valid typemath starts with "=" or an operation before the "=" (Example: "+=")
Example typemath use:
`create number one = value 1`
`create number two = number 1 + number 1`
- Operators
  - String Operators
    - `+` Add Operator is the Only Operator Supported
  - Number Operators
    - `+` Add Operator
    - `-` Subtract Operator
    - `*` Multiply Operator
    - `/` Divide Operator
typemath from number to string and string to number is allowed
The "value" type will instert the name as a value

### Control Flow Commands
- End:
  - The "end" command ends the current program
  - Example:
  - `end`
- If Statements:
  - If Statements compare two variables and if the condition is true, will run the code after it
  - Example if Statement:
  - `if number one = number two print value "They are equal!"`

#### I/O Commands
- `print (value/number/string) **name/value** ...`
  - Prints the values of all variables and values listed before printing a newline
  - Examples:
    - `print value "Hello World!"`
      - Result: "Hello World!\n"
    - `print value "Hello " value "World!"`
      - Result: "Hello World!\n"
- `output (value/number/string) **name/value** ...`
  - Same as the print command except it does not print a newline at the end
  - Examples:
    - `output value "Hello World!"`
      - Result: "Hello World!"
- `input (number/string) **name** ...`
  - Gets user input for all variables listed (They must be created first)
    - Example:
      - `create number count`
      - `input number count`

##### Branching Commands
- `mark **name**`
  - Mark the location as a location in the program to goto later
  - Examples
    - `mark loop`
- `goto (line/offset/mark) **name/number**`
  - Go to the label or line in the program and start running from there
  - "Lines" in Turl:
    - Lines are every line in the file that has a command (Everything except "mark", empty line, and commented lines)
    - Lines are 0 index
  - Examples:
    - `goto mark loop`
    - `goto offset 10`
    - `goto offset -10`
    - `goto line 20`

###### Turl Errors
- "Low Operand Count"
  - The instruction is too short or the instruction does not exist
- "Invalid __ Type"
  - The type used can't be used in the command
- "__Math Error"
  - The Typemath statement was bad
- "__ Reference Error"
  - A variable was referenced that was not created yet

