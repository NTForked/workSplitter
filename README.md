# workSplitter
Run a set of commands, one-per-machine at a time on a list of machines via ssh

Uses pstreams to keep track of the ssh processes for me.  
Developed since I wanted to run a set of slow jobs on a cluster, one job per machine at a time.
