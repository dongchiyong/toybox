-module(tut9).
-export([test_if/2]).

test_if(A, B) -> 
	if
		A == 1 ->
			io:format("A = 1~n", []);
		B == 2 ->
			io:format("B = 2~n", []);
		A == 2, B == 3 ->
			io:format("A = 2,B = 3~n", []);
		A == 2 ; B == 4 ->
			io:format("A = 2,B = 4~n", []);
		true ->
			other
	end.