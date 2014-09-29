
#include <string>
#include <unistd.h>
#include <cstring>
#include "client.cpp"

int reciveCoords()
{
    tcp_client c;
    string host;
/*
    cout<<"Enter hostname : ";
    cin>>host;
*/

    host = "127.0.0.1";
    //connect to host
    c.conn(host , 6555);
     
    //send some data

    int i, j;

    while (true){

        c.send_data("{\"category\": \"tracker\",\"request\" : \"get\",\"values\": [ \"frame\" ]}");
         
        //receive and echo reply
        cout<<"----------------------------\n\n";

        string s(c.receive(2048));
        
        if (s.length()){
            
            i = 0;
            while(s.data()[i]!='x' && i<s.length()){
                i++;
            }
    
            if (i==s.length()){
                cout << s << endl;
                return 0;
            };
    
            i+=3;

            j=i;
            while(s.data()[j]!=',' && j<s.length()){
                j++;
            }
    
            if (j==s.length()){
                cout << s << endl;
                return 0;
            };
    
            string x = s.substr(i,j-i);

            i = j;
            while(s.data()[i]!='y'  && i<s.length()){
                i++;
            }
    
            if (i==s.length()){
                cout << s << endl;
                return 0;
            };
    
            i+=3;

            j=i;
            while(s.data()[j]!='}' && j<s.length()){
                j++;
            }

    
            if (j==s.length()){
                cout << s << endl;
                return 0;
            };
    
            string y = s.substr(i,j-i);

            cout << "x: " << x << " " << "y: " << y << endl;

        };

        usleep(100000);

    };

    //done
    return 0;

};

/*

#include "client.cpp"
#include "cpp-json/json.h"

int main(int argc , char *argv[])
{
    tcp_client c;
    string host;
     
    cout<<"Enter hostname : ";
    cin>>host;
     
    //connect to host
    c.conn(host , 6555);
     
    //send some data
    c.send_data("{\"category\": \"tracker\",\"request\" : \"get\",\"values\": [ \"frame\" ]}");
     
    //receive and echo reply
    cout<<"----------------------------\n\n";
    //cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";

    json::value json = json::parse(c.receive(1024);

    auto aux = json["values"]["frame"]["avg"];
    //done
    return 0;
}*/
