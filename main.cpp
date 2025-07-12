#include <iostream>
#include <chrono>
#include <unordered_map>
#include <iomanip>
#include <array>

int findFirstDayOfYear(int year){
    time_t t=time(nullptr);
    tm * timeinfo=localtime(&t);
    int currentYear=(timeinfo->tm_year) + 1900;
    int totalYears=year-currentYear;
    int days{};
    if(totalYears<0){
        for(int y=year;y<year+abs(totalYears);++y){
            if(y%4==0) days +=366;
            else days +=365;
        }
        days +=(timeinfo->tm_yday)+1;
        int i=1;
        while(i<currentYear){
            if(days%7==0) std::cout<<i<<std::endl;
            ++i;
        }
        days =(days%7)-1;
        return (7-days+timeinfo->tm_wday)%7;

    }
    else if(totalYears>0){
        for(int y=currentYear+1;y<year;++y){
            if(y%4==0) days +=366;
            else days +=365;
        }
        if(currentYear%4==0) days += 366-(timeinfo->tm_yday);
        else days += 365-(timeinfo->tm_yday);
        days =(days%7);
        return (timeinfo->tm_wday+days)%7;
    }
    
    return ((timeinfo->tm_wday)+7-(timeinfo->tm_yday%7))%7;;
}

int main(){
    size_t year{};
    std::cout<<"Enter a year : ";
    std::cin>>year;
    //std::cout<<"Enter the first day of the year [0:Sunday,1:Monday ... 6:Saturday]: ";
    //std::cin>>first_day;
    std::cout<<"\nCalender for "<<year<<std::endl;
    std::array<std::string,12> months {"January","February","March","April","May","June","July","August","September","October","November","December"};
    std::array<int,12> noOfDays {31,28,31,30,31,30,31,31,30,31,30,31};
    //std::unordered_map<std::string,int> months_map {{"January",31},{"February",28},{"March",31},{"April",30},{"May",31},{"June",30},{"July",31},{"August",31},{"September",30},{"October",31},{"November",30},{"December",31}};
    const std::string DAY[]={"Sun","Mon","Tue",
    "Wed","Thu","Fri","Sat"};
    int first_day=findFirstDayOfYear(year);
    std::cout<<DAY[first_day]<<std::endl;

    int startOfNextMonth=first_day;
    for(int i{0};i<months.size();++i){

        std::cout<<"--"<<months[i]<<" "<<year<<" --"<<std::endl;
        std::cout<<std::setw(6)<<"Sun"<<std::setw(6)<<"Mon"<<std::setw(6)<<"Tue"<<std::setw(6)<<"Wed"<<std::setw(6)<<"Thu"<<std::setw(6)<<"Fri"<<std::setw(6)<<"Sat"<<std::endl;

        int j{};
        while(j<startOfNextMonth){
            std::cout<<std::setw(6)<<" ";
            ++j;
        }
        if(year%4==0 and i==1) noOfDays[i]=29;
        j=0;
        while(j<(noOfDays[i])){
            if(j!=0 && (j+startOfNextMonth)%7==0) std::cout<<'\n';
            std::cout<<std::setw(6)<<j+1;
            ++j;
        }
        
        startOfNextMonth = (startOfNextMonth+noOfDays[i])%7;
        std::cout<<'\n'<<std::endl;        
        } 
    return 0;
}