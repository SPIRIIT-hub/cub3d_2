#include "headers/cub3d.h"

#define mapWidth 14
#define mapHeight 33
#define screenWidth 1000
#define screenHeight 1000
#define moveSpeed 1
#define rotSpeed 0.0872665

double zBuffer[5000];

// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
//   {1,0,2,2,2,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,2,2,2,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
//   {1,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

void			ft_clear(t_rc *rc)
{
	int x = rc->pars->Ry;
	int y = rc->pars->Rx;

	while (x--)
	{
		while (y--)
			my_mlx_pixel_put(rc, y, x, 0);
		y = rc->pars->Rx;
	}
}

char	*get_pixel(t_img *data, int x, int y)
{
	char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (dst);
}

void            my_mlx_pixel_put(t_rc *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	//printf("here . %x\n", *(unsigned int*)dst);
	*(unsigned int*)dst = color;
}

void	ft_verLine(int x, int drawstart, int drawend, t_rc *rc)
{
	int imgx;
	int imgy;
	int len = drawend - drawstart;
	int wle = 0;
	// printf("camera : %f\n", rc->planeX); (rc->txtn[rc->side]->img_height - 1) -
	// if (x == 512)
	// 	printf("side : %d\n", rc->sd);
	if (rc->sd == 3 || rc->sd == 1)
		imgx = (rc->txtn[rc->sd]->img_width - 1) -  ((int)(rc->txtn[rc->sd]->img_width * (rc->wallX - (int)rc->wallX)));
	else
	{
		imgx = (int)(rc->txtn[rc->sd]->img_width * (rc->wallX - (int)rc->wallX));
	}
	
	imgy = (int)(((rc->txtn[rc->sd]->img_height - 1) / (double)len) * wle);
	while (wle < drawstart)
	{
		// my_mlx_pixel_put(rc, x, wle, 0x008DFF);
		my_mlx_pixel_put(rc, x, wle, ((rc->pars->C_R << 16) | ((rc->pars->C_G << 8) | rc->pars->C_B)));
		wle++;
	}
	wle = 0;
	while (wle < len)
	{
		imgy = (int)((((rc->txtn[rc->sd]->img_height - 1)) / (double)len) * wle);
		// printf("rc->wallX : %f\n", rc->wallX);
		if(drawstart > 0 && !(drawstart >= rc->pars->Ry))
			my_mlx_pixel_put(rc, x, drawstart, *(unsigned int*)get_pixel(rc->txtn[rc->sd], imgx, imgy));
		wle++;
		drawstart++;
	}
	wle = drawend;
	while (wle < rc->pars->Ry)
	{
		// my_mlx_pixel_put(rc, x, wle, 0x067802);
		my_mlx_pixel_put(rc, x, wle, ((rc->pars->F_R << 16) | ((rc->pars->F_G << 8) | rc->pars->F_B)));
		wle++;
	}
}

void	ft_spriteLine(int x, int drawstart, int drawend, int color, t_rc *rc)
{
	int imgx;
	int imgy;
	int len = drawend - drawstart;
	int wle = 0;

	imgx = (int)(rc->txtn[4]->img_width * (rc->wallX - (int)rc->wallX));
	imgy = (int)(((rc->txtn[4]->img_height - 1) / (double)len) * wle);
	while (wle < len)
	{
		imgy = (int)(((rc->txtn[4]->img_height - 1) / (double)len) * wle);
		// printf("rc->wallX : %f\n", rc->wallX);
		my_mlx_pixel_put(rc, x, drawstart, *(unsigned int*)get_pixel(rc->txtn[4], imgx, imgy));
		wle++;
		drawstart++;
	}
}

int				ft_close(int keycode, t_rc *rc)
{
	exit(0);
	return (1);
}

int             key_hook(int keycode, t_rc *rc)
{
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	if (keycode == KEY_W)
    {
      if(rc->pars->map[(int)(rc->posX + rc->dirX * moveSpeed)][(int)(rc->posY)] != '1') rc->posX += rc->dirX * moveSpeed;
      if(rc->pars->map[(int)(rc->posX)][(int)(rc->posY + rc->dirY * moveSpeed)] != '1') rc->posY += rc->dirY * moveSpeed;
	  ft_clear(rc);
	  ft_Raycaster(rc);
    }
    //move backwards if no wall behind you
    if (keycode == KEY_S)
    {
      if(rc->pars->map[(int)(rc->posX - rc->dirX * moveSpeed)][(int)(rc->posY)] != '1') rc->posX -= rc->dirX * moveSpeed;
      if(rc->pars->map[(int)(rc->posX)][(int)(rc->posY - rc->dirY * moveSpeed)] != '1') rc->posY -= rc->dirY * moveSpeed;
	  ft_clear(rc);
	  ft_Raycaster(rc);
    }
    //rotate to the right
    if (keycode == KEY_D)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = rc->dirX;
      rc->dirX = rc->dirX * cos(-rotSpeed) - rc->dirY * sin(-rotSpeed);
      rc->dirY = oldDirX * sin(-rotSpeed) + rc->dirY * cos(-rotSpeed);
      double oldPlaneX = rc->planeX;
      rc->planeX = rc->planeX * cos(-rotSpeed) - rc->planeY * sin(-rotSpeed);
      rc->planeY = oldPlaneX * sin(-rotSpeed) + rc->planeY * cos(-rotSpeed);
	  ft_clear(rc);
	  ft_Raycaster(rc);
	//   printf("%f %f %f %f\n", rc->dirX, rc->dirY, rc->planeX, rc->planeY);
    }
    //rotate to the left
    if (keycode == KEY_A)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = rc->dirX;
      rc->dirX = rc->dirX * cos(rotSpeed) - rc->dirY * sin(rotSpeed);
      rc->dirY = oldDirX * sin(rotSpeed) + rc->dirY * cos(rotSpeed);
      double oldPlaneX = rc->planeX;
      rc->planeX = rc->planeX * cos(rotSpeed) - rc->planeY * sin(rotSpeed);
      rc->planeY = oldPlaneX * sin(rotSpeed) + rc->planeY * cos(rotSpeed);
	  ft_clear(rc);
	  ft_Raycaster(rc);
	//   printf("%f %f %f %f\n", rc->dirX, rc->dirY, rc->planeX, rc->planeY);
    }
	return (0);
}

int		ft_isalreadyset(t_rc *rc, int mapX, int mapY)
{
	int i = 0;

	while (rc->sprX[i])
	{
		if (rc->sprX[i] == mapX)
		{
			i = 0;
			while (rc->sprY[i])
			{
				if (rc->sprY[i] == mapY)
					return (1);
				i++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

void	ft_Raycaster(t_rc *rc)
{
	int x = 0;
	rc->sprindex = -1;
	for(int x = 0; x < rc->pars->Rx; x++)
    {
		//calculate ray position and direction
		rc->cameraX = 2 * x / (double)(rc->pars->Rx) - 1; //x-coordinate in camera space
		rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
		rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
		//which box of the map we're in
		int mapX = (int)(rc->posX);
		int mapY = (int)(rc->posY);
		int sprite = 0;

		//length of ray from current position to next x or y-side
		// double sideDistX;
		// double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		rc->deltaDistX = fabs(1 / rc->rayDirX);
		rc->deltaDistY = fabs(1 / rc->rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		// int side; //was a NS or a EW wall hit?

		// Alternative code for deltaDist in case division through zero is not supported
		rc->deltaDistX = (rc->rayDirY == 0) ? 0 : ((rc->rayDirX == 0) ? 1 : fabs(1 / rc->rayDirX));
		rc->deltaDistY = (rc->rayDirX == 0) ? 0 : ((rc->rayDirY == 0) ? 1 : fabs(1 / rc->rayDirY));

		//calculate step and initial sideDist
		if (rc->rayDirX < 0)
		{
			stepX = -1;
			rc->sideDistX = (rc->posX - mapX) * rc->deltaDistX;
		}
		else
		{
			stepX = 1;
			rc->sideDistX = (mapX + 1.0 - rc->posX) * rc->deltaDistX;
		}
		if (rc->rayDirY < 0)
		{
			stepY = -1;
			rc->sideDistY = (rc->posY - mapY) * rc->deltaDistY;
		}
		else
		{
			stepY = 1;
			rc->sideDistY = (mapY + 1.0 - rc->posY) * rc->deltaDistY;
		}
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (rc->sideDistX < rc->sideDistY)
			{
				rc->sideDistX += rc->deltaDistX;
				mapX += stepX;
				rc->side = 0;
				rc->sd = 0;
			}
			else
			{
				rc->sideDistY += rc->deltaDistY;
				mapY += stepY;
				rc->side = 1;
				rc->sd = 1;
			}
			//Check if ray has hit a wall
			// if (worldMap[mapX][mapY] == 2){
			// 	sprite += 1;
			// 	if ((mapX == 8 && mapY == 2 && !ft_isalreadyset(rc, mapX, mapY)) || ((!rc->sprX[rc->sprindex] || !rc->sprY[rc->sprindex]) || !ft_isalreadyset(rc, mapX, mapY))) //  || !(rc->sprX[rc->sprindex] == mapX && rc->sprY[rc->sprindex] == mapY)
			// 	{
			// 		printf("here%d %d %d|", rc->sprindex, mapX, mapY);
			// 		rc->sprindex++;
			// 		rc->sprX[rc->sprindex] = mapX;
			// 		rc->sprX[rc->sprindex + 1] = 0;
			// 		rc->sprY[rc->sprindex] = mapY;
			// 		rc->sprY[rc->sprindex + 1] = 0;
			// 	}
			// }
			// int u = 0;
			// while (rc->pars->map[u])
			// {
			// 	printf("%s\n", rc->pars->map[u]);
			// 	u++;
			// }
			// printf("%d\n", mapX);
			if (rc->pars->map[mapX][mapY] == '1') hit = 1;
		}
		
		if (rc->side == 0)	perpWallDist = (mapX - rc->posX + (1 - stepX) / 2) / rc->rayDirX;
		else				perpWallDist = (mapY - rc->posY + (1 - stepY) / 2) / rc->rayDirY;
		int lineHeight = (int)(rc->pars->Ry / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + rc->pars->Ry / 2;
		// if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + rc->pars->Ry / 2;
		// if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

		// int color;
		// // printf("worldMap[mapX][mapY] : %d\n", worldMap[mapX][mapY]);
		// switch(rc->pars->map[mapX][mapY])
		// {
		// 	case 1:  color = 0xFF2D00; break; //red
		// 	case 2:  color = 0x00911F; break; //green
		// 	case 3:  color = 0x00B9FF; break; //blue
		// 	case 4:  color = 0xFFFFFF; break; //white
		// 	default: color = 0xFBFF00; break; //yellow
		// }

		//give x and y sides different brightness
		// if (rc->side == 1) {color = color / 2;}

		// printf("here %f %f\n", rayDirY, rayDirX);
		// printf("ici : %f %f\n", deltaDistX, deltaDistY);
		//draw the pixels of the stripe as a vertical line

		if (rc->side == 0)
		{
			rc->wallX = rc->posY + perpWallDist * rc->rayDirY;
			if (rc->rayDirX > 0)
				rc->sd = 3;
		}
		else
		{
			rc->wallX = rc->posX + perpWallDist * rc->rayDirX;
			if (rc->rayDirY > 0)
				rc->sd = 2;
		}
		zBuffer[x] = perpWallDist;
		ft_verLine(x, drawStart, drawEnd, rc);
		// printf("here : %f %f\n", rc->sideDistX, rc->sideDistY);
	}
	ft_spritedata(rc);
	ft_sprite(rc);
	if (rc->save == 1)
		save_bmp("save.bmp", rc);
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img, 0, 0);
}

void	ft_spritedata(t_rc *rc)
{
	int i = 0;
	int j = 0;

	while (i < rc->pars->hmap)
	{
		while (j < rc->pars->lenmax)
		{
			if (rc->pars->map[i][j] == '2')
			{
				rc->sprindex++;
				rc->sprX[rc->sprindex] = i;
				rc->sprX[rc->sprindex + 1] = 0;
				rc->sprY[rc->sprindex] = j;
				rc->sprY[rc->sprindex + 1] = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_sprite(t_rc *rc)
{
	int i = 0;
	int order[rc->sprindex + 1];

	double spriteDistance[10000];
	while (i <= rc->sprindex)
	{
		spriteDistance[i] = ((rc->posX - rc->sprX[i]) * (rc->posX - rc->sprX[i]) + (rc->posY - rc->sprY[i]) * (rc->posY - rc->sprY[i]));
		i++;
	}
	i = 0;
	double tmp = 0;
	int tmp1 = 0;
	int j = 0;
	while (j <= rc->sprindex)
	{
		order[j] = j;
		j++;
	}
	j = 0;
	while (i <= rc->sprindex)
	{
		j = i;
		while (j <= rc->sprindex)
		{
			if (spriteDistance[i] < spriteDistance[j])
			{
				tmp = spriteDistance[i];
				spriteDistance[i] = spriteDistance[j];
				spriteDistance[j] = tmp;
				tmp1 = order[i];
				order[i] = order[j];
				order[j] = tmp1;
			}
			j++;
		}
		i++;
	}
	i = 0;
	
	while (i <= rc->sprindex)
	{
		double spriteX = rc->sprX[order[i]] - rc->posX + 0.5;
		double spriteY = rc->sprY[order[i]] - rc->posY + 0.5;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (rc->planeX * rc->dirY - rc->dirX * rc->planeY); //required for correct matrix multiplication

		double transformX = (invDet * (rc->dirY * spriteX - rc->dirX * spriteY));
		double transformY = (invDet * (-rc->planeY * spriteX + rc->planeX * spriteY)); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((rc->pars->Rx / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(rc->pars->Ry / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + rc->pars->Ry / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + rc->pars->Ry / 2;
		if(drawEndY >= rc->pars->Ry) drawEndY = rc->pars->Ry - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (rc->pars->Ry / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= rc->pars->Rx) drawEndX = rc->pars->Rx - 1;

		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * rc->txtn[4]->img_width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < rc->pars->Rx && transformY < zBuffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - rc->pars->Ry * 128 + spriteHeight * 128;  //256 and 128 factors to avoid floats
					int texY = ((d * rc->txtn[4]->img_height) / spriteHeight) / 256;
					// long color = rc->txtn[4]->addr[rc->txtn[4]->img_height * texY + texX];
					// rc->addr[(y * screenWidth + stripe)] = color;
					// if((color & 0x00FFFFFF) != 0)
					if (*(unsigned int*)get_pixel(rc->txtn[4], texX, texY) != 0)
						my_mlx_pixel_put(rc, stripe, y, *(unsigned int*)get_pixel(rc->txtn[4], texX, texY));
				}
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_rc rc;
	rc.posX = 3;
	rc.posY = 3;  //x and y start position
  	
	rc.txtn = wrmalloc(sizeof(t_img *) * 5);
	char **map;

	if (argc <= 0 || (rc.pars = ismapvalid(argv, argc)) == NULL)
	{
		printf("Error, map invalid\n");
		return (0);
	}
	// printf("pos %c\n", rc.pars->position);
	if (rc.pars->position == 'S')
	{
		rc.dirX = 1;
		rc.dirY = 0; //initial direction vector
		rc.planeX = 0;
		rc.planeY = -0.66; //the 2d raycaster version of camera plane
	}
	else if (rc.pars->position == 'N')
	{
		rc.dirX = -1;
		rc.dirY = 0; //initial direction vector
		rc.planeX = 0;
		rc.planeY = 0.66; //the 2d raycaster version of camera plane
	}
	else if (rc.pars->position == 'E')
	{
		rc.dirX = 0;
		rc.dirY = 1; //initial direction vector
		rc.planeX = 0.66;
		rc.planeY = 0; //the 2d raycaster version of camera plane
	}
	else
	{
		rc.dirX = 0;
		rc.dirY = -1; //initial direction vector
		rc.planeX = -0.66;
		rc.planeY = 0; //the 2d raycaster version of camera plane
	}
	
	// rc.planeX = 0;
	// rc.planeY = -0.66; //the 2d raycaster version of camera plane


	if (argc == 3 && argv[2][0] == '-' && argv[2][1] == '-' && argv[2][2] == 's' && argv[2][3] == 'a' && argv[2][4] == 'v' && argv[2][5] == 'e')
		rc.save = 1;
	else
	{
		rc.save = 0;
	}
	
	// printf("SAVE : %d\n", rc.save);

	if (rc.pars->Rx > 5120 / 2)
		rc.pars->Rx = 5120 / 2;
	if (rc.pars->Ry > 2880 / 2)
		rc.pars->Ry = 2880 / 2;

	rc.posX = rc.pars->yplayer + 0.5;
	rc.posY = rc.pars->xplayer + 0.5;

	int i = 0;
	int j = 0;
	i = 0;
	while (rc.pars->map[i])
	{
		j = 0;
		while (rc.pars->map[i][j])
		{
			printf("%c", rc.pars->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	while (rc.pars->map[i] != NULL)
	{
		i++;
	}
	rc.pars->hmap = i;
	printf("width %d\nheight %d\n", rc.pars->Rx, rc.pars->Ry);
	i = 0;
	// exit(0);
	while (i < 5)
	{
		rc.txtn[i] = wrmalloc(sizeof(t_img));
		i++;
	}
	rc.mlx = mlx_init();
    rc.win = mlx_new_window(rc.mlx, rc.pars->Rx, rc.pars->Ry, "RayCaster");
	mlx_hook(rc.win, 2, 1L<<0, key_hook, &rc);
	mlx_hook(rc.win, 17, 0, ft_close, &rc);
	mlx_loop_hook(rc.mlx, key_hook, &rc);
	rc.img = mlx_new_image(rc.mlx, rc.pars->Rx, rc.pars->Ry);
    rc.addr = mlx_get_data_addr(rc.img, &rc.bits_per_pixel, &rc.line_length, &rc.endian);

	if (!(rc.txtn[0]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoNO, &rc.txtn[0]->img_width, &rc.txtn[0]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[0]->addr = mlx_get_data_addr(rc.txtn[0]->img, &rc.txtn[0]->bits_per_pixel, &rc.txtn[0]->line_length, &rc.txtn[0]->endian);
	
	if (!(rc.txtn[1]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoWE, &rc.txtn[1]->img_width, &rc.txtn[1]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[1]->addr = mlx_get_data_addr(rc.txtn[1]->img, &rc.txtn[1]->bits_per_pixel, &rc.txtn[1]->line_length, &rc.txtn[1]->endian);

	if (!(rc.txtn[2]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoEA, &rc.txtn[2]->img_width, &rc.txtn[2]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[2]->addr = mlx_get_data_addr(rc.txtn[2]->img, &rc.txtn[2]->bits_per_pixel, &rc.txtn[2]->line_length, &rc.txtn[2]->endian);

	if (!(rc.txtn[3]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoSO, &rc.txtn[3]->img_width, &rc.txtn[3]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[3]->addr = mlx_get_data_addr(rc.txtn[3]->img, &rc.txtn[3]->bits_per_pixel, &rc.txtn[3]->line_length, &rc.txtn[3]->endian);

	if (!(rc.txtn[4]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoS, &rc.txtn[4]->img_width, &rc.txtn[4]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[4]->addr = mlx_get_data_addr(rc.txtn[4]->img, &rc.txtn[4]->bits_per_pixel, &rc.txtn[4]->line_length, &rc.txtn[4]->endian);
	
	ft_Raycaster(&rc);
	if (rc.save == 1)
		save_bmp("save.bmp", &rc);
	mlx_put_image_to_window(rc.mlx, rc.win, rc.img, 0, 0);
	mlx_loop(rc.mlx);
}