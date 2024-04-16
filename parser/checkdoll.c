#include "../minishell.h"

void check_money(t_mini *mini)
{
    t_lexer *tmp;

    tmp = mini->lexer;
    while(tmp)
    {
        if(srch_index_c(tmp->content, '$') != 0)
        {
            est ce qu on split est ce qu on join est ce qu on suce 
        }
    }


}