#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
#include <fcntl.h>
#define KEY_D 2
#define KEY_S 1 
#define KEY_A 0
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53
#define PI 3.14159265359

typedef struct		s_list
{
      void			*content;
      struct s_list	*next;
}					t_list;

typedef struct  	s_img {
		int    	bits_per_pixel;
		int    	line_length;
		int     endian;
		char    *addr;
		void    *img;
    	char    *relative_path;
    	int     img_width;
		int     img_height;
}               	t_img;

typedef struct	s_struct
{
	int				lenmax; // width de la map
	int				hmap; // height de la map
	int				Rx; // Width
	int				Ry; // Height
	int				i;
	int				F_R; //couleur sol
	int				F_G;
	int				F_B;
	int				C_R; //couleur ciel
	int				C_G;
	int				C_B;
	int				northside;
	char			position; //orientation WNES
	int				xplayer; //px
	int				yplayer; //py
	char			*pathtoNO;
	char			*pathtoSO;
	char			*pathtoWE;
	char			*pathtoEA;
	char			*pathtoS;
	char			*args[8];
	char			**map;
}				t_struct;

typedef struct  	s_rc {
        void    	*mlx;
        void    	*win;
		void    	*img;
		char    	*addr;
		int     	bits_per_pixel;
		int     	line_length;
		int     	endian;
        double      posX;
        double      posY;
        double      dirX;
        double      dirY;
        double      planeX;
        double      rayDirX;
        double      rayDirY;
        double      planeY;
        double      cameraX;
        double      sideDistX;
		double      sideDistY;
		double		deltaDistX;
		double		deltaDistY;
		double		wallX;
		int			side;
		int			sd;
		int			sprindex;
		int			sprX[100000];
		int			sprY[100000];
        t_img       **txtn;
		t_struct	*pars;
}               	t_rc;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
int				ft_lstsize(t_list *lst);
t_list			*makelst(int fd, t_struct *mstruct);
int				getlenmax(t_list **alst);
char			**fromlsttotab(t_list **alst, t_struct *mstruct);
char			**fillthetabwithspaces(char **tab, t_struct *mstruct);
void			structinit(t_struct *mstruct);
int				checkthenorth(char **tab, t_struct *mstruct);
int				checkalltab(char **tab, t_struct *mstruct);
int				checkspaces(char **tab, t_struct *mstruct, int i, int j);
int				checkthemap(char **tab, t_struct *mstruct);
t_struct		*ismapvalid(char **arv, int arc);
int				ft_atoi(const char *nptr);
size_t			ft_cmpt(char const *s, char c);
char			*ft_free(char **tab, size_t i);
char			**ft_mem(char const *s, char c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			checkelemR(char *line, t_struct *mstruct);
char			*checktheid(char *line, char a, char b);
void			checkelemF(char *line, t_struct *mstruct);
void			checkelemC(char *line, t_struct *mstruct);
int				checktheorder(char **tab, t_struct *mstruct);
char			*ft_strcpy(char *dst, const char *src, size_t dstsize);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(const char *s);
static size_t	ft_check(char c, char const *set);
static char		*ft_putzero(char *str, size_t i);
char			*ft_strtrim(char const *s1, char const *set);
int				shouldiskip(char *line, t_struct *mstruct, int a);
char			*ft_strdup(const char *s);
int				checkplayerposition(char **tab, t_struct *mstruct);
char			*fromdoubletosimple(char **tab, t_struct *mstruct);
int				ft_strcmp(char *s1, char *s2);
void			maketab(t_struct *mstruct);
int				whatstheid(char *line, t_struct *mstruct);
int				firstpartmap(char *line, t_struct *mstruct, int y);


void            my_mlx_pixel_put(t_rc *data, int x, int y, int color);
int             key_hook(int keycode, t_rc *vars);
void	        ft_Raycaster(t_rc *vars);
int				wrfree(void *ptr);
void			*wrmalloc(unsigned long size);
void			wrdestroy(void);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_sprite(t_rc *rc);
int				ft_close(int keycode, t_rc *rc);
void			ft_spritedata(t_rc *rc);

//--------------------------------------------------------------------------------------------------


#endif