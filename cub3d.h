/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:15:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 04:02:37 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H

#define CUB3D_H

#include <math.h>
#include "get_next_line/get_next_line.h"
#include "minilibx/mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct	s_img
{
	void	*window;
	void	*image;
	char	*data;
	int		bpp; 
	int		sizeline;
	int		endian;
	int		img_h;
	int		img_w;
}				t_img;
/*
typedef struct s_texture{
	void	*image;
	char	*path;
	char	*data;
	int		use;
	int		w;
	int		h;
	int		bpp;
	int		sizeline;
	int		endian;
}			t_texture;
*/
typedef struct	s_player{
	double		dir_x;
	double		dir_y;
	double		speed;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
	int			map_y;
	int			map_x;
	double		camera_x;
	double		camera_y;
	double		raydir_x;
	double		raydir_y;
	double		deltadist_x;
	double		deltadist_y;
	double		sidedist_x;
	double		sidedist_y;
	int			move_x;
	int			move_y;
	int			face_of_cube;
	double		distance;
	int			wall_height;
	int			beginning_of_the_walls;
	int			end_of_the_walls;
	double		wall_x;
	double		wall_y;
	int			text_x;
	int			text_y;
	double		text_pos;
	double		text_step;
}				t_player;

typedef struct		s_map
{
	char			*north_text;
	char			*south_text;
	char			*west_text;
	char			*east_text;
	char			*map_p;
	char			**map;
	int				map_length;
	int				*rgb_c;
	int				*rgb_f;
	int	rgb_ceiling;
	int	rgb_floor;
	int				rgb_control;
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	int				img_h;
	int				img_w;
}					t_map;

typedef struct	s_mlx
{
	void	*mlx_init;
	void	*mlx_img;
	int		*mlx_img_addr;
	void	*mlx_window;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx;

typedef struct	s_setting
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	double		move_speed;
	double		rot_speed;
	int			press_w;
	int			press_a;
	int			press_s;
	int			press_d;
	int			direct_right;
	int			direct_left;
}				t_setting;

void	ft_init(t_setting *set);
int		ft_free_str(t_setting *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(char *s1);

int		check_texts_rgb(t_map *map, char *av1);
void	ft_check_xpm(t_map *map);
int		take_texts(char *str, t_map *map, int i, int flg);
int		create_map_dp(t_map *map);
int		valid_char(char *str);
int		valid_map(t_map *map);
int		where_am_i(t_setting *set, char **str);
void	mlx_start(t_setting *set);
int		my_screen(t_setting *set);
int		close_win(t_setting *set);
int		press_key (int	keycode, t_setting *set);
int		release_key(int keycode, t_setting *set);
void	ray_casting (t_setting *set);
void	ft_get_images(t_setting *set, t_player	*player, int j);
void	check_keys(t_setting *set);
void	ft_images_management(t_mlx *mlx, t_map *map);
void	ft_init_mlx(t_mlx *mlx);

# define	TEXT_W 64
# define	TEXT_H 64
# define 	WIDTH	640
# define	HEIGHT 640

# define	W 13
# define	A 0
# define	S 1
# define	D 2
# define	ESC 53
# define	RIGHT 124
# define	LEFT 123

#endif


/*

** altta ayrıca 2. bi map varsa diye newline kontrolü var, 
öylesine newline varsa map geçersiz sayılıyor
-------------------
 As such, I came up with a few map validation rules. Assume that we are scanning the map from top to bottom, left to right :

 Ignore all leading whitespaces.
 If the current row is the 0th row or the final row, only accept '1’s and ’ 's.
 else, The first and final character should always be a ‘1’.
 In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1’s or ’ 's.
 If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be ‘1’
 If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be ‘1’
-------------------
https://hackmd.io/@nszl/H1LXByIE2
*/


/*
Bakış Yönünü Hesaplayın: Oyuncunun bakış yönünü hesaplamak için 
oyuncunun pozisyonundan hedef noktasına doğru bir vektör oluşturun. 
Bu vektör, oyuncunun bakış yönünü temsil eder. Bu vektörü NDC koordinatlarına dönüştürebilirsiniz, 
ancak bu hesaplamayı yapmak için dönüşüm matrislerine ihtiyacınız olabilir.

Yönü Kontrol Edin: Elde ettiğiniz bakış yönü vektörünün bileşenlerini 
kontrol ederek, oyuncunun hangi yöne baktığını belirleyebilirsiniz. 
Örneğin, bakış yönü vektörünün x bileşeni pozitifse, oyuncu doğuya bakıyor demektir. 
Yönlerin NDC koordinatlarındaki karşılıklarını dikkate alarak bu kontrolü yapabilirsiniz.

mlx_loop_hook ile ilgili bilgi:Örneğin, eğer bir uygulama 60 FPS (Frame Per Second) ile çalışıyorsa, 
mlx_loop_hook ile belirtilen işlev her saniyede 60 kez çağrılacaktır. Bu, düzenli bir animasyon veya 
grafik güncellemesi için uygun bir hızdır. Ancak, bu hız uygulama ve donanım özelliklerine göre değişebilir. (YUHHH) (solongda kullanmıştım :)

*/


/*
MERT

mlx destroy lazım

Fonksiyon isimlerinin başında ft_



*/