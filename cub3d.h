/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:25 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 15:21:01 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE		4096

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

# define RESX				1000
# define RESY				1000

# define ROTATE_LEFT		123
# define ROTATE_RIGHT		124
# define FORWARD_W_Z		13
# define BACK_S_S			1
# define RIGHT_D_D			2
# define LEFT_A_Q			0
# define ESC				53
# define MINIMAP			46
# define MOUSE				6

# define RES				1000
# define SIZE				15
# define GROUND				0x00000000
# define WALL				0x00FFFFFF
# define SPRITE				0x00FFFF00
# define PLAYER				0x0000FF00
# define CEILING			0x0099FFFF

// # ifdef Darwin
// #  define SYS 	1
// # endif

// # ifdef Linux
// #  define SYS	2
// # endif

// -------- STRUCTURES ---------------

typedef struct s_sprxy
{
	double		x;
	double		y;
}	t_sprxy;

typedef struct s_sprite
{
	int			nbspr;
	int			*order;
	double		*dist;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstartx;
	int			drawstarty;
	int			drawendy;
	int			drawendx;
	int			spritewidth;
	double		*zbuffer;
}	t_sprite;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	int			minimap;
	int			width;
	int			height;
	void		*img2;
	int			*addr2;
}					t_data;

typedef struct s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planx;
	double		plany;
	double		raydirx;
	double		raydiry;
	double		camerax;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		movespeed;
	double		rotspeed;
	int			x;
	int			texture;
}					t_ray;

	// // double		dirx;//vecteur de direction
	// // double		diry;//vecteur de direction
	// // double		planx;//vecteur du plan
	// // double		plany;//vecteur du plan
	// // double		raydirx;//calcul de direction x du rayon
	// // double		raydiry;//calcul de direction y du rayon
	// // double		camerax;//point x sur la plan camera :
	//					Gauche ecran = -1,
	// 				milieu = 0, droite = 1
	// // int			mapx;//coordonée x du carré dans lequel est pos
	// // int			mapy;// coordonnée y du carré dans lequel est pos
	// // double		sidedistx;//distance que le rayon parcours jusqu'au
	// 				premier point d'intersection vertical
	// // double		sidedisty;//distance que le rayon parcours jusqu'au 
	// 				premier point d'intersection horizontal
	// // double		deltadistx;//distance que rayon parcours entre chaque 
	// 				point d'intersection vertical
	// // double		deltadisty;//distance que le rayon parcours entre 
	// 				chaque point d'intersection horizontal
	// // int			stepx;// -1 si doit sauter un carre dans 
	// 				direction x negative, 1 dans la direction x positive
	// // int			stepy;// -1 si doit sauter un carre dans la 
	// 				direction y negative, 1 dans la direction y positive
	// // int			hit;// 1 si un mur a ete touche, 0 sinon
	// // int			side;// 0 si c'est un cote x qui est touche (vertical), 
	// 				1 si un cote y (horizontal)
	// // double		perpwalldist;// distance du rayon
	// // int			lineheight;//hauteur de la ligne a dessiner
	// // int			drawstart;//position de debut ou il faut dessiner
	// // int			drawend;//position de fin ou il faut dessiner

typedef struct s_texture
{
	int			texdir;
	double		wallx;
	int			texx;
	int			texy;
	double		step;
	double		texpos;
}					t_texture;

	// int			texdir; //direction no, s, ea, we de la texture
	// double		wallx; // valeur où le mur a été touché : coordonnée 
				// y si side == 0, coordonnée x si side == 1
	// int			texx; // coordonnée x de la texture
	// int			texy; // coordonée y de la texture
	// double		step; // indique de combien augmenter 
				// les coordonnées de la texture pour chaque pixel
	// double		texpos; // coordonnée de départ

typedef struct s_game
{
	int			i;
	int			rx;
	int			ry;
	int			sizeline;
	int			nbline;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f;
	int			sumf;
	int			verifyf;
	int			*floor;
	int			c;
	int			sumc;
	int			verifyc;
	int			*ceiling;
	int			indic1;
	int			indic2;
	char		**map;
	char		**check;
	char		depart;
	int			dx;
	int			dy;
	int			inmap;
	t_sprite	sp;
	t_sprxy		*sxy;
	t_data		texture[5];
	t_data		data;
	t_ray		ray;
	t_texture	t;
}	t_game;

// --------- PARSING ------------------
//parse.c
int		check_filename(char *str, t_game *game);
void	ft_parsing(char *fichier, t_game *game);
void	ft_parsing2(int ret, char *str, t_game *game, int fd);
int		ft_parsing_map(char *fichier, t_game *game);
int		ft_mlx(t_game *game);

//init.c
void	ft_init(t_game *game);
void	ft_init_help(t_game *game);
void	ft_init_sprite(t_game *game);
void	ft_init_sprite2(t_game *game, int i, int j, int v);
void	ft_init2(t_game *game);

//init2.c
void	ft_init22(t_game *game);
void	ft_init3(t_game *game);
void	check_first_last(t_game *game);

//parse_info.c
void	ft_color_resolution(char **str, t_game *game);
int		create_rgb(int	*color);
int		ft_atoi2(const char *str, t_game *game);
void	ft_texture(char *str, t_game *game);
int		ft_path_texture(char *str, char **texture, t_game *game, int j);

//parse_info2.c
int		*ft_atoi_f(const char *str, t_game *game);
int		ft_atoi_f2(t_game *game, int temp, const char *str, int t);
int		*ft_atoi_c(const char *str, t_game *game);
int		ft_atoi_c2(t_game *game, int temp, const char *str, int t);
void	default_fc(t_game *game);

//parse_map.c
void	ft_map(char *str, t_game *game);
int		ft_is_map(char *str);
int		ft_copy_map(char *str, t_game *game);
int		check_map(char *fichier, t_game *game);
void	check_map2(t_game *game);

//parse_map2.c
int		ft_copy_check(char *str, t_game *game);
void	check_close(int i, int j, t_game *game);
int		ft_start(char c, t_game *game, int i, int j);
int		ft_charinstr(char *str, char c);
int		ft_mapstart(char *str);

// ---------- UTILS ---------------------
//utils.c
int		ft_strlen2(char *str);

//error.c
void	ft_error_start(char *str);
void	ft_error(t_game *game, char *str);
void	ft_error2(t_game *game);
int		ft_exit(t_game *game);
void	ft_verify_errors(t_game *game);

//texture.c
void	ft_get_texture(t_game *game);
void	ft_get_texture_adress(t_game *game);
void	ft_draw_texture(t_game *game, int x, int y);
void	ft_init_texture(t_game *game);

//texture2.c
void	ft_get_texture2(t_game *game);
void	ft_get_texture3(t_game *game);

//mlx_utils.c
int		ft_key_press(int keycode, t_game *game);
int		ft_mouse(int x, int y, t_game *game);
int		ft_key_release(int keycode, t_game *game);

//minimap.c
void	print_minimap(t_game *game);
void	print_minimap2(t_game *game);
void	put_case(int x, int y, int color, t_game *game);
void	put_player_case(int color, t_game *game);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// --------- RAYCASTING --------------------
//raycasting.c
int		ft_raycasting(t_game *game);
void	ft_stepsidedist(t_game *game);
int		ft_color_column(t_game *game);

//raycasting_utils.c
void	ft_incrementray(t_game *game);
void	ft_drawstartend(t_game *game);
void	ft_swap(t_game *game);

//sprites.c
void	ft_dist_order(t_game *game);
void	ft_dist_order2(t_game *game);
void	ft_calculs(t_game *game, int i);
void	ft_draw_spr(t_game *game, int y, int texX, int stripe);
void	ft_sprite(t_game *game);

//raycasting_moves.c
void	ft_forward_back(t_game *game);
void	ft_left_right(t_game *game);
void	ft_rotate_right(t_game *game);
void	ft_rotate_left(t_game *game);

#endif