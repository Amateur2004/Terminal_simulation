char hostname[100];
char* username;
char path[100];
char ini_shell[400];
char help[5]="help";
char ex[5]="exit";
char ls[3]="ls";
char ls1[3]="-l";
char ls2[3]="-t"; //modification time
char ls3[3]="-u"; //access time
char ls4[3]="-U"; //creation time
char cp[3]="cp";
char cp1[3]="-i";
char cp2[3]="-u";
char cp3[3]="-v";
char cp4[3]="-f";
char mv[3]="mv";
char mv1[3]="-i"; //ask to overwrite
char mv2[3]="-u"; //only when file is new
char mv3[3]="-v"; //verbose explains what is done
char mv4[3]="-f"; //forceful
char g[5]="grep";
char g1[3]="-c"; //count no.of matching lines
char g2[3]="-h"; //without filename in start
char g3[3]="-l"; // with name of files
char g4[3]="-n"; //line number along with matching line
char ps[3]="ps";
char ps1[3]="-T"; //related to terminal PID SPID TTY TIME CMD
char ps2[3]="-e"; //regardless of terminal all process PID TTY TIME CMD
char ps3[4]="-eT"; //related to terminal PID SPID TTY TIME CMD
char ps4[4]="-Te";

