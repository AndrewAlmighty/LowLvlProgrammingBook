%define lw 0

%macro colon 2
%%lw: dq lw
db %1, 0	;this is string
xt_ %+ %2

%define lw %%lw
%endmacro
