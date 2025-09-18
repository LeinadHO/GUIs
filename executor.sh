gcc $1/main.c \
    funcoes-externas/AUX_WaitEventTimeoutCount/AUX_WaitEventTimeoutCount.c \
    funcoes-externas/Colisoes/colidiu.c \
    funcoes-externas/MultiplosCliques/MultiplosCliques.c \
    -I funcoes-externas/AUX_WaitEventTimeoutCount \
    -I funcoes-externas/Colisoes \
    -I funcoes-externas/MultiplosCliques \
    -lSDL2 -lSDL2_gfx -lSDL2_image -o "$1/$1"
./$1/$1