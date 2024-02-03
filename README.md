# automatonsim
**automatonsim** is a program for simulating automatons. The program runs in the command line and the user enters commands to create the automaton and perform transformations and checks on it.

## Features
- Making an automaton epsilon-free
- NFA to DFA conversion
- Minimizing a DFA

## Compiling
Clone **automatonsim** to your computer:
```
git clone https://github.com/BaumGuard/automatonsim
```
Compile the program:
```
make
```

## Usage
**automatonsim** comes with a little scripting language that allows the user to create an automaton and interact with it.<br />

Start the program:
```
./automatonsim
```

### Creating a state
Syntax:
```
state (<state name> <state type>)+
```

### Creating a transition
Syntax:
```
transition <source state> <destination state> <symbol>
```

### Making the automaton epsilon-free
```
make epsilon free
```

### Making the automaton deterministic
```
make deterministic
```

### Minimizing the automaton
```
minimize
```

### Printing the description of a automaton
<table>
  <tr>
    <td><code>description</code></td>
    <td>Print the description of the automaton created by the user</td>
  </tr>
  <tr>
    <td><code>epsilon free description</code></td>
    <td>Print the description of the epsilon-free automaton</td>
  </tr>
  <tr>
    <td><code>deterministic description</code></td>
    <td>Print the description of the deterministic automaton (DFA)</td>
  </tr>
  <tr>
    <td><code>minimal description</code></td>
    <td>Print the description of the minimized automaton</td>
  </tr>
</table>

### Check if the automaton accepts a word
Syntax:
```
check <word>
```

### Get the epsilon closure of a state
Syntax:
```
epsilon closure <state>
```
