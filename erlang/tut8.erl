-module(tut8).
-export([list_reverse/1]).

list_reverse(List) -> list_reverse(List, []).

list_reverse([Head | Tail], Reversed) -> list_reverse(Tail, [Head | Reversed]);
list_reverse([], Reversed) -> Reversed.
