#include<bits/stdc++.h>


using namespace std;

int toss(){
    return rand()%2;
}

int nextRun(){
    vector<int>run;
    run={0,1,2,3,4,6,-1};
    int random=rand()%7;
    return run[random];
}


class Player{
    public:
        string name;
        int runScored=0;
        int ballsPlayed=0;
        int ballsBowled=0;
        int wicketTaken=0;
        int runsGiven=0;
       
        Player(string name){
            this->name=name;
        }
       
       
        void playerDetails(){
            cout<<endl;
            cout<<"<--------Player Details-------->"<<endl;
            cout<<endl;
            cout<<"Player: "<<name<<endl
            <<"Run Scored: "<<runScored<<endl
            <<"Ball Plyed: "<<ballsPlayed<<endl
            <<"Ball Bowled: "<<ballsBowled<<endl
            <<"Wicket Taken: "<<wicketTaken<<endl
            <<"Runs Given: "<<runsGiven<<endl;
        }
       
};


class Team{
    public:
        string name;
        int gamesPlayed=0;
        int gamesWon=0;
        int gamesLost=0;
        int runScored=0;
        int runsGiven=0;
        int ballsPlayed=0;
        int ballsBowled=0;
        int wicketTaken=0;
       
        vector<Player>players;
       
        Team( string name = ""){
            this->name=name;
        }
       
        void addPlayer(string name){
            this->players.push_back(Player(name));
        }
       
        void printTeamDetails(){
            cout<<endl;
            cout<<"<--------Team Details-------->"<<endl;
            cout<<endl;
            cout<<"Team: "<<name<<endl
            <<"Games Played: "<<gamesPlayed<<endl
            <<"Games Won: "<<gamesWon<<endl
            <<"Games Lost: "<<gamesLost<<endl
            <<"Games Draw : "<<gamesPlayed-gamesLost-gamesWon<<endl
            <<"Runs Scored : "<<runsGiven<<endl
            <<"Runs Given : "<<runsGiven<<endl
            <<"Balls Palyed : "<<ballsPlayed<<endl
            <<"Balls Bowled: "<<ballsBowled<<endl
            <<"Wicket Taken: "<<wicketTaken<<endl;
        }
};

struct TeamCompare
{
   bool operator() (const Team& lhs, const Team& rhs) const
   {
       return lhs.gamesWon <= rhs.gamesWon;
   }
};

class Match{
    public:
        int matchID;
        string team1,team2;
        int teamScore1=0,teamScore2=0;
        int teamWicket1=0,teamWicket2=0;
       
        vector<string>commentry;
       
        Match(int id,string team1,string team2){
            this->matchID=id;
            this->team1=team1;
            this->team2=team2;
        }
       
        void playInning(Team &battingTeam, Team &bowlingTeam, int &score, int &wickets,string Inning){
            cout<<"\nInning: "+Inning+ " Batting - " <<battingTeam.name<<"<----------------->"<<"Bowling - "<<bowlingTeam.name<<endl;
           int maxWicket = battingTeam.players.size();
            for(int overs=0;overs<2;overs++){
                for(int ball=0;ball<6;ball++){
                    int run = nextRun();
                    
                    string bowler = bowlingTeam.players[overs].name;
                    string batsMan = battingTeam.players.begin()->name;
                    if(run == -1){
                        wickets++;
                        commentry.push_back("Wicket! Batsman: " + batsMan+ ", Bowler: "+ bowler + "Total Runs : " + to_string(score) +"/" + to_string(wickets)+ ", Over: " + to_string(overs) + "." +to_string(ball+1));
                        if(wickets == maxWicket-1){
                            return;
                        }
                         battingTeam.players.erase(battingTeam.players.begin());
                    }else{
                        score+=run;
                        commentry.push_back("Total Runs : " + to_string(score) +"/" + to_string(wickets)+ ", Batsman: "+ batsMan +", Bowler: "+ bowler +", Over: " + to_string(overs) + "." +to_string(ball+1));
                    }
                    
                    battingTeam.runScored=score;
                    battingTeam.ballsPlayed++;
                    bowlingTeam.ballsBowled++;
                    
                    if(score > bowlingTeam.runScored && bowlingTeam.ballsPlayed>0)
                    {
                        // cout<<score<<" "<<bowlingTeam.runScored<<" "<<bowlingTeam.ballsPlayed<<endl;
                        return;
                    }
                }
            }
        }
        
        void printCommentry()
        {
            for(auto it:commentry)
            {
                cout<<it<<" "<<endl;
            }
        }
        
        void printMatchDetails(){
            cout<<"Match ID: "<<matchID<<endl
            <<"Team 1: "<<team1<<", Score: "<<teamScore1<< "/" << teamWicket1<<endl
             <<"Team 2: "<<team2<<", Score: "<<teamScore2<< "/" << teamWicket2<<endl
              <<"Result: "<<(teamScore1>=teamScore2 ? (teamScore1==teamScore2 ?"Match Draw" : team1 + " won!" ): team2 +" won!")<<endl;
           
        }
       
       
};

class IPL{
    private:
        map<string,Team> teams;
        vector<Match>matches;
    public:
        void addTeam(const std::string& teamName){
            teams[teamName]=Team(teamName);
        }
       
        void addPlayer(string teamName,string playerName){
            teams[teamName].addPlayer(playerName);
        }
       
        void printTeamDetails(){
            for(auto it:teams){
                it.second.printTeamDetails();
            }
        }
       
        void printPlayerDetails(){
            for(auto it:teams){
                for(auto itr:it.second.players){
                    itr.playerDetails();
                }
            }
        }
       
       
        void playMatch(int matchID, string teamName1, string teamName2, int toss){
           
            Match match(matchID,teamName1,teamName2);
            Team &team1=teams[teamName1];
            Team &team2=teams[teamName2];
           
           
            if(toss){
                cout<<endl
                <<team1.name<<" won the toss and decided to bat first---->"<<endl;
                 match.playInning(team1,team2,match.teamScore1,match.teamWicket1,"1st");
                 cout<< "\t<---------------commentry inning 1--------------->\n"<<endl;
                 match.printCommentry();
                 match.commentry.clear();
                 match.playInning(team2,team1,match.teamScore2,match.teamWicket2,"2nd");
                //  commetry.clear();
                 cout<< "\t<---------------commentry inning 2--------------->\n"<<endl;
                 match.printCommentry();
            }
            else{
                cout<<endl
                <<team2.name<<" won the toss and decided to bat first---->\n"<<endl;
                 match.playInning(team1,team2,match.teamScore1,match.teamWicket1,"1st");
                 cout<< "\t<---------------commentry inning 1--------------->"<<endl;
                 match.printCommentry();
                 match.commentry.clear();
                 match.playInning(team2,team1,match.teamScore2,match.teamWicket2,"2nd");
                 cout<< "\t<---------------commentry inning 2--------------->\n"<<endl;
                 match.printCommentry();
                 
            }
           
            matches.push_back(match);
            
            match.printMatchDetails();
        }
       
        void printMatchDetails(int matchID){
            for(auto it:matches){
                if(it.matchID==matchID){
                    it.printMatchDetails();
                    return;
                }
            }
            cout<<"Match Not Found!!"<<endl;
        }
};



int main(){
   
     srand(time(0));
     IPL ipl;
 
    ipl.addTeam("RCB");
    ipl.addTeam("CSK");
    ipl.addTeam("RR");
   
    ipl.addPlayer("RCB","Virat");
    ipl.addPlayer("RCB","Dinesh");
    ipl.addPlayer("RCB","Duplesis");
    ipl.addPlayer("RCB","ABD");
    ipl.addPlayer("RCB","Gayel");
    ipl.addPlayer("RCB","Md Siraj");
   
   
    ipl.addPlayer("CSK","Dhoni");
    ipl.addPlayer("CSK","Raina");
    ipl.addPlayer("CSK","Ashwin");
    ipl.addPlayer("CSK","Rituraj");
    ipl.addPlayer("CSK","Shivam Dubey");
    ipl.addPlayer("CSK","Jadeja");
   
    ipl.playMatch(rand()%222,"RCB","CSK",toss());
    //ipl.printMatchDetails(123);
   
    return 0;
}