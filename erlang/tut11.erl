-module(tut11).
-export([month_days/2]).

month_days(Year, Month) ->
	Lead = if
		trunc(Year / 400) * 400 == Year -> lead;
		trunc(Year / 100) * 100 == Year -> not_lead;
		trunc(Year / 4) * 4 == Year -> lead;
		true -> not_lead
	end,
	
	case Month of
		jan -> 31;
		feb when Lead == lead -> 29;
		feb -> 28;
		mar -> 31;
		apr -> 30;
		may -> 31;
		jun -> 30;
		jul -> 31;
		aug -> 31;
		sep -> 30;
		oct -> 31;
		nov -> 30;
		dec -> 31
	end.