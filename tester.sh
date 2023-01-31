./pipex in "$1" "$2" "$3" false
< in $1 | $2 | $3 > true    

diff true false