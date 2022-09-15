# Koral

Koral is a work-in-progress, dynamically-typed scripting language. It's simple, easy to use and still in development. It's written in Python but may switch to CPython in the future due to the speed upgrade.

## Syntax

The language doesn't have if statements and loops yet, but they will be implemented on a later date.

Here is a basic program:
```js
var example = "Hello World!"
var number = 5 * 5 * 4

say(example)
say(number)
```

Output:
```
Hello World!
100
```

## Building

### Requirements
  * Python 3
 
### Run
To run the language, the code needs to be written in a .kor file. To run it, type:
```
python main.py `koral file`
```
The output will be displayed in the terminal and you can look at the data folder to see how the language compiles.

## Contributing
Koral is still in development. If you want to contribute in any way, feel free to text me. To learn more, check `CONTRIBUTIONS.md`.