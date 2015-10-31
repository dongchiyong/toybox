-module(tut16).
-export([start/0,ping/1,pong/0]).

ping(0) ->
	pong1 ! finised,
	io:format("ping finished~n", []);
ping(N)->
	pong1 ! {ping, self()},
	receive
		pong ->
			io:format("Ping received pong~n", [])
	end,
	ping(N-1).
	
pong() ->
	receive 
		finished ->
			io:format("Pong finished~n", []);
		{ping, Ping_PID}->
			io:format("Pong received ping~n", []),
			Ping_PID !pong,
			pong()
		end.
		
start() ->
	register(pong1,spawn(tut16, pong, [])),
	spawn(tut16, ping, [3]).