-module(tut6).
-export([list_max/1]).

list_max([Head|Tail])->list_max(Head, Tail).

list_max(Max, []) -> Max;
list_max(Max, [Head | Tail])	when Max > Head -> list_max(Max, Tail).
list_max(Max, [Head | Tail]) -> list_max(Head, Tail).
