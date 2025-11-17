#ifndef SIGNALS_H
# define SIGNALS_H

void	setup_signal_handlers(void);
void	cleanup_signal_handlers(void);
void	signal_handler(int signum);

#endif
