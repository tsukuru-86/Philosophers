all:
	$(MAKE) -C philo

bonus:
	$(MAKE) -C philo_bonus

clean:
	$(MAKE) -C philo clean
	$(MAKE) -C philo_bonus clean

fclean:
	$(MAKE) -C philo fclean
	$(MAKE) -C philo_bonus fclean

re: fclean all bonus

.PHONY: all bonus clean fclean re
