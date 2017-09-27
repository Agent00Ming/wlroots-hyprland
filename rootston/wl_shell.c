#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wayland-server.h>
#include <wlr/types/wlr_box.h>
#include <wlr/types/wlr_surface.h>
#include <wlr/types/wlr_wl_shell.h>
#include <wlr/util/log.h>
#include "rootston/desktop.h"
#include "rootston/server.h"
#include "rootston/input.h"

void handle_wl_shell_surface(struct wl_listener *listener, void *data) {
	struct roots_desktop *desktop =
		wl_container_of(listener, desktop, wl_shell_surface);

	struct wlr_wl_shell_surface *surface = data;
	wlr_log(L_DEBUG, "new wl_shell surface");
	//wlr_wl_shell_surface_ping(surface);

	struct roots_wl_shell_surface *roots_surface =
		calloc(1, sizeof(struct roots_wl_shell_surface));
	// TODO: all of the trimmings

	struct roots_view *view = calloc(1, sizeof(struct roots_view));
	view->type = ROOTS_WL_SHELL_VIEW;
	view->x = view->y = 200;
	view->wl_shell_surface = surface;
	view->roots_wl_shell_surface = roots_surface;
	//view->wlr_surface = surface->surface;
	//view->get_input_bounds = get_input_bounds;
	//view->activate = activate;
	view->desktop = desktop;
	roots_surface->view = view;
	wl_list_insert(&desktop->views, &view->link);
}
