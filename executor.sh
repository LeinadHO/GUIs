gcc $1/main.c \
    funcoes-externas/AUX_WaitEventTimeoutCount/AUX_WaitEventTimeoutCount.c \
    funcoes-externas/Colisoes/colidiu.c \
    -I funcoes-externas/AUX_WaitEventTimeoutCount \
    -I funcoes-externas/Colisoes
    -lSDL2 -lSDL2_gfx -o "$1"
./$1/$1