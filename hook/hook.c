#include "../headers/cub3d.h"

int	ft_close(int keycode, t_rc *rc)
{
	exit(0);
	return (1);
}

static void	hook_WS(int keycode, t_rc *rc)
{
	if (keycode == KEY_W)
	{
		if (rc->pars->map[(int)(rc->posX + rc->dirX * moveSpeed)]
			[(int)rc->posY] != '1')
			rc->posX += rc->dirX * moveSpeed;
		if (rc->pars->map[(int)rc->posX]
			[(int)(rc->posY + rc->dirY * moveSpeed)] != '1')
			rc->posY += rc->dirY * moveSpeed;
		ft_Raycaster(rc);
	}
	if (keycode == KEY_S)
	{
		if (rc->pars->map[(int)(rc->posX - rc->dirX * moveSpeed)]
			[(int)rc->posY] != '1')
			rc->posX -= rc->dirX * moveSpeed;
		if (rc->pars->map[(int)rc->posX]
			[(int)(rc->posY - rc->dirY * moveSpeed)] != '1')
			rc->posY -= rc->dirY * moveSpeed;
		ft_Raycaster(rc);
	}
}

void	hook_AD(int keycode, t_rc *rc)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == KEY_D)
	{
		oldDirX = rc->dirX;
		rc->dirX = rc->dirX * cos(-rotSpeed) - rc->dirY * sin(-rotSpeed);
		rc->dirY = oldDirX * sin(-rotSpeed) + rc->dirY * cos(-rotSpeed);
		oldPlaneX = rc->planeX;
		rc->planeX = rc->planeX * cos(-rotSpeed) - rc->planeY * sin(-rotSpeed);
		rc->planeY = oldPlaneX * sin(-rotSpeed) + rc->planeY * cos(-rotSpeed);
		ft_Raycaster(rc);
		return ;
	}
	oldDirX = rc->dirX;
	rc->dirX = rc->dirX * cos(rotSpeed) - rc->dirY * sin(rotSpeed);
	rc->dirY = oldDirX * sin(rotSpeed) + rc->dirY * cos(rotSpeed);
	oldPlaneX = rc->planeX;
	rc->planeX = rc->planeX * cos(rotSpeed) - rc->planeY * sin(rotSpeed);
	rc->planeY = oldPlaneX * sin(rotSpeed) + rc->planeY * cos(rotSpeed);
	ft_Raycaster(rc);
}

int	key_hook(int keycode, t_rc *rc)
{
	if (keycode == KEY_ESC)
	{
		wrdestroy();
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_S)
	{
		hook_WS(keycode, rc);
	}
	if (keycode == KEY_D || keycode == KEY_A)
	{
		hook_AD(keycode, rc);
	}
	return (0);
}
