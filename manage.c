#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

#define COLOR_DARK_GRAY 8
#define COLOR_YELLOW_BROWN 9

int number_of_units=0;
char *week[5]={"saturday","sunday","monday","tuesday","wensday"};

struct day
{
    int day_name;
    int time_name;
};

struct deadline 
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;   
};

struct unit
{
    char *name;
    char *teacher;
    int days_number;
    struct day *date;
    struct deadline final_exam;
};

void edit_name(struct unit *vahed,WINDOW *win)
{
    vahed->name=malloc(100*sizeof(char));
    wgetstr(win,vahed->name);
}

void edit_teacher(struct unit *vahed,WINDOW *win)
{
    vahed->teacher=malloc(100*sizeof(char));
    wgetstr(win,vahed->teacher);
}

void edit_date(struct unit *vahed,WINDOW *win)
{
    for(int i=0; i<vahed->days_number; i++)
    {
        werase(win);
        mvwprintw(win,0,0,"enter the day: ");
        mvwprintw(win,1,0,"1. Saturday");
        mvwprintw(win,2,0,"2. Sunday");
        mvwprintw(win,3,0,"3. Monday");
        mvwprintw(win,4,0,"4. tuesday");
        mvwprintw(win,5,0,"5. wendesday\n");
        char *day_name=malloc(20*sizeof(char));
        wgetstr(win,day_name);
        vahed->date[i].day_name=atoi(day_name);

        werase(win);
        mvwprintw(win,0,0,"enter the hour: ");
        mvwprintw(win,1,0,"1. 7/30-9");
        mvwprintw(win,2,0,"2. 9-10/30");
        mvwprintw(win,3,0,"3. 10/30-12");
        mvwprintw(win,4,0,"4. 12-13");
        mvwprintw(win,5,0,"5. 13-14/30");
        mvwprintw(win,6,0,"6. 14/30-16");
        mvwprintw(win,7,0,"7. 16-17/30\n");
        char *time_name=malloc(10*sizeof(char));
        wgetstr(win,time_name);
        vahed->date[i].time_name=atoi(time_name);
        
    }
}

void edit_final_exam_date(struct unit *vahed, WINDOW *win)
{
    werase(win);
    mvwprintw(win,0,0,"enter the final exam date: \nenter the year: ");
    char*year=malloc(10*sizeof(char));
    wgetstr(win,year);
    vahed->final_exam.year=atoi(year);

    mvwprintw(win,3,0,"enter the month: ");
    char*month=malloc(10*sizeof(char));
    wgetstr(win,month);
    vahed->final_exam.month=atoi(month);

    mvwprintw(win,5,0,"enter the day: ");
    char*day=malloc(10*sizeof(char));
    wgetstr(win,day);
    vahed->final_exam.day=atoi(day);

    mvwprintw(win,7,0,"enter the hour: ");
    char*hour=malloc(10*sizeof(char));
    wgetstr(win,hour);
    vahed->final_exam.hour=atoi(hour);

    mvwprintw(win,9,0,"enter the mintue: ");
    char*minute=malloc(10*sizeof(char));
    wgetstr(win,minute);
    vahed->final_exam.minutes=atoi(minute);
}


struct unit add_unit(WINDOW *win)
{
    number_of_units++;
    struct unit vahed;

    //adding name;
    werase(win);
    mvwprintw(win,0,0,"enter the name of lesson: ");
    edit_name(&vahed,win);

    //adding teacher
    werase(win);
    mvwprintw(win,0,0,"enter the name of teacher: ");
    edit_teacher(&vahed,win);

    //adding date
    werase(win);
    mvwprintw(win,0,0,"enter the number of days of lesson in week: ");
    char *days=malloc(10*sizeof(char));
    wgetstr(win,days);
    vahed.days_number=atoi(days);

    vahed.date=malloc(vahed.days_number*sizeof(struct day));
    edit_date(&vahed,win);

    // adding final exam
    werase(win);
    mvwprintw(win,0,0,"enter the final exam date: ");
    edit_final_exam_date(&vahed,win);
    werase(win);

    return vahed;
}

void delete_unit(struct unit *vaheds,int position)
{
    free(vaheds[position].name);
    free(vaheds[position].teacher);
    free(vaheds[position].date);
    for(int i=position; i<number_of_units-1; i++)
    {
        struct unit temp=vaheds[i+1];
        vaheds[i+1]=vaheds[i];
        vaheds[i]=temp;
    }
    number_of_units--;
    vaheds=realloc(vaheds,number_of_units*sizeof(struct unit));
}

void display(struct unit *vaheds)
{
    initscr();
    start_color();

    init_color(COLOR_DARK_GRAY,300, 450, 600); 
    init_color(COLOR_YELLOW_BROWN, 900, 850, 700);
    init_pair(1, COLOR_YELLOW_BROWN, COLOR_DARK_GRAY);

    
    WINDOW *win=newwin(47,154,0,0);
    WINDOW *win_time=newwin(5,150,1,2);
    WINDOW *win_saturday=newwin(8,150,6,2);
    WINDOW *win_sunday=newwin(8,150,14,2);
    WINDOW *win_monday=newwin(8,150,22,2);
    WINDOW *win_tuesday=newwin(8,150,30,2);
    WINDOW *win_wensday=newwin(8,150,38,2);

    WINDOW *win_array[5]={win_saturday,win_sunday,win_monday,win_tuesday,win_wensday};

    wbkgd(win,COLOR_PAIR(1));
    wbkgd(win_time,COLOR_PAIR(1));
    wbkgd(win_saturday,COLOR_PAIR(1));
    wbkgd(win_sunday,COLOR_PAIR(1));
    wbkgd(win_monday,COLOR_PAIR(1));
    wbkgd(win_tuesday,COLOR_PAIR(1));
    wbkgd(win_wensday,COLOR_PAIR(1));


    box(win_time,0,0);
    box(win_saturday,0,0);
    box(win_sunday,0,0);
    box(win_monday,0,0);
    box(win_tuesday,0,0);
    box(win_wensday,0,0);


    vaheds[0]=add_unit(win);

    mvwprintw(win_saturday,0,2,"Saturday");
    mvwprintw(win_sunday,0,2,"Sunday");
    mvwprintw(win_monday,0,2,"Monday");
    mvwprintw(win_tuesday,0,2,"Tuesday");
    mvwprintw(win_wensday,0,2,"wednesday");

    mvwprintw(win_time,2,20,"7/30 - 9");
    mvwprintw(win_time,2,38,"9 - 10/30");
    mvwprintw(win_time,2,56,"10/30 - 12");
    mvwprintw(win_time,2,74,"12 - 13");
    mvwprintw(win_time,2,92,"13 - 14/30");
    mvwprintw(win_time,2,110,"14/30-16");
    mvwprintw(win_time,2,128,"16 - 17/30");

    wrefresh(win);
    wrefresh(win_time);
    wrefresh(win_saturday);
    wrefresh(win_sunday);
    wrefresh(win_monday);
    wrefresh(win_tuesday);
    wrefresh(win_wensday);


    int choice=-1;

    while(choice !='q')
    {
        werase(win);
        werase(win_saturday);
        werase(win_sunday);
        werase(win_monday);
        werase(win_tuesday);
        werase(win_wensday);


        box(win_time,0,0);
        box(win_saturday,0,0);
        box(win_sunday,0,0);
        box(win_monday,0,0);
        box(win_tuesday,0,0);
        box(win_wensday,0,0);

        mvwprintw(win_saturday,0,2,"Saturday");
        mvwprintw(win_sunday,0,2,"Sunday");
        mvwprintw(win_monday,0,2,"Monday");
        mvwprintw(win_tuesday,0,2,"Tuesday");
        mvwprintw(win_wensday,0,2,"wednesday");

        mvwprintw(win_time,2,20,"7/30 - 9");
        mvwprintw(win_time,2,38,"9 - 10/30");
        mvwprintw(win_time,2,56,"10/30 - 12");
        mvwprintw(win_time,2,74," 12 - 13");
        mvwprintw(win_time,2,92,"13 - 14/30");
        mvwprintw(win_time,2,110,"14/30-16");
        mvwprintw(win_time,2,128,"16 - 17/30");

        wrefresh(win);
        wrefresh(win_time);
        wrefresh(win_saturday);
        wrefresh(win_sunday);
        wrefresh(win_monday);
        wrefresh(win_tuesday);
        wrefresh(win_wensday);

        for(int i=0; i<number_of_units; i++)
        {
            for(int j=0; j<vaheds[i].days_number; j++)
            {
                for(int k=0; k<5; k++)
                {
                    if(vaheds[i].date[j].day_name==(k+1))
                    {
                        int position=vaheds[i].date[j].time_name-1;
                        wattron(win_array[k],A_BOLD);
                        mvwprintw(win_array[k],1,22+position*18,"%s",vaheds[i].name);
                        wattroff(win_array[k],A_BOLD);
                        mvwprintw(win_array[k],3,22+position*18,"%s",vaheds[i].teacher);
                        mvwprintw(win_array[k],4,22+position*18,"%d/%d/%d",vaheds[i].final_exam.year,vaheds[i].final_exam.month,vaheds[i].final_exam.day);
                        mvwprintw(win_array[k],5,22+position*18,"%d.%d",vaheds[i].final_exam.hour,vaheds[i].final_exam.minutes);
                        wrefresh(win_array[k]);
                    }
                }
            }
        }

        noecho();
        choice=wgetch(win_saturday);
        switch(choice)
        {
            //adding task;
            case 'a':
                echo();
                vaheds=realloc(vaheds,(number_of_units+1)*sizeof(struct unit));
                vaheds[number_of_units]=add_unit(win);
                werase(win);
                noecho();
                break;
            
            //enable editing
            case 'e':
                noecho();
                int highlight_edit=0;
                int choice_edit=-1;
               

                while(choice_edit !='e')
                {
                    WINDOW *win_edit=newwin(47,160,0,0);
                    wbkgd(win_edit,COLOR_PAIR(1)); 
                    wrefresh(win_edit);

                    for(int i=0; i<number_of_units; i++)
                    {
                        if(i==highlight_edit) wattron(win_edit,A_REVERSE);
                        mvwprintw(win_edit,i,0,"%d. %s",i+1,vaheds[i].name);
                        wattroff(win_edit,A_REVERSE);
                    }


                    choice_edit=wgetch(win_edit);
                    switch(choice_edit)
                    {
                        case 's':
                            highlight_edit++;
                            if(highlight_edit==number_of_units) highlight_edit=number_of_units-1;
                            break;

                        case 'w':
                            highlight_edit--;
                            if(highlight_edit==-1) highlight_edit=0;
                            break;

                        case 'f':
                            echo();
                            werase(win);
                            edit_final_exam_date(&vaheds[highlight_edit],win);
                            werase(win);
                            noecho();
                            break;

                        case 't':
                            echo();
                            edit_date(&vaheds[highlight_edit],win);
                            werase(win);
                            noecho();
                            break;

                        case 'd':
                            delete_unit(vaheds,highlight_edit);
                            break;
                    }
                    werase(win_edit);
                }
                break;
            
            
        }
    }

}

int main()
{
    struct unit *vahed=malloc(1*sizeof(struct unit));

    display(vahed);
    endwin();

    return 0;
}