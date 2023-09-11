# for spaces before new line
s/( {1,}(\r$))|( {1,}($))/\2/g


#Double line comments
/(\/\*\*)/,/(\*\*\/)/p
/(\/\*\*)/,/(\*\*\/)/d

#Single line comments
/(^\#)|(^.*\/\/)/p
/(^\#)|(^.*\/\/)/d


#for binary operators surrounded by space
s/(\S)([\<\>\*\-\+\<=\>=\/\=\==])(\S)/\1 \2 \3/g ### do the zero or more s

#Fixes multiple spaces between tokens
s/(\S) {2,}(\S)/\1 \2/g

# deleting spaces in parentheses
s/(\() {1,}(.*) {1,}(\))/\1\2\3/g
