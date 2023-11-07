# Turl Syntax
> All Of The Planned Features Of Turl
> All Names Will Be Able To Be Adjusted with turl.lang
## Turl Commands
- create [type..., name]
  - Creates a variable of a certain type and name
  - > `create byte number` , `create string hello`
  - list [type]:
    - Creates a list of a certain type
    - > `create list string users`
- byte [name]
  - Gets a byte of memory
  - > `byte name`
- string [name]
  - Gets the value of a string
  - > `string name`
- value [value]
  - Is used to introduce preset values into the program
  - > `value 3`
- list [type,name,(at/last/first/byte)]
  - Gets a value from a list
  - > `list string users at 1` , `list string users byte userid` , `list string users first` , `list string user last`
- = [type, name]
  - Sets the previous referenced byte to a value or the value of another byte
  - > `byte 1 = value 2` , `byte 1 = byte 2`
- Math Operators (Only work after an '=' sign)
  - \+ [type, name] (works with byte and string)
    - Adds following value to previous value (only works after '=')
    - > `byte result = byte a + byte b` , `string helloworld = string hello + string world`
  - \- [type, name] (works with byte)
    - Subtracts following value from previous value (only works after '=')
    - > `byte result = byte a - byte b`
  - \* [type, name] (works with byte)
    - Multiplies following value by previous value (only works after '=')
    - > `byte result = byte a * byte b`
  - / [type, name] (works with byte)
    - Divides following value by previous value (only works after '=')
    - > `byte result = byte a / byte b`
- print [type, name, ...]
  - Prints the value of a variable in the console
  - > `print byte name` , `print string name` , `print value "hello world"`
  - > ***...** example:* `print value "ID:" byte ID`
- input [type]
  - Asks user for input
  - > `string a = input string`
### Example Program:
- Variable Example Program:  
  `create byte number = value 1`
  - Creates a byte named number and sets it to 1  
  `create byte newNumber = value 5`  
  - Creates a byte named newNumber and sets it to 5  
  `byte number = byte newNumber`
  - Sets the byte named number to the value of the byte named newNumber  
- Input Output Example Program:
  `create string hello = value "Hello, " + input string + value "!"`  
  - Create a string named hello which is set to "Hello, 'string user input'!"
    - 'string user input' is input from the console processed as a string (Turl Code is `input string` )  
  `print string hello`  
  - Output the string named hello to the console