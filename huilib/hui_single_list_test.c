#include <stdlib.h>
#include "hui_single_list.h"

int main()
{
	int i;
	int test_data[5]={3,2,4,5,1};

	HuiSingleList *list = create_list();
	if (!list)
		return 0;

	for(i = 0; i < sizeof(test_data)/sizeof(test_data[0]); ++i){
		push_back(list, test_data[i]);
	}

	dump_list(list);

	reverse_list(list);
	
	dump_list(list);

	return 0;
}
