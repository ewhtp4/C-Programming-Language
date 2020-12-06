#!/bin/bash
spinner()
{
    local pid=$1
    local delay=0.75
    local spinstr='|/-\'
    while [ "$(ps a | awk '{print $1}' | grep $pid)" ]; do
        local temp=${spinstr#?}
        printf " [%c]  " "$spinstr"
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        printf "\b\b\b\b\b\b"
    done
    printf "    \b\b\b\b"
}
cat << "EOF"
clear
gnome-terminal -e
                                   #*                                           
                                #######,                                        
                              ##########                                        
                           ,(###########                                        
                          (((((######(((                                        
                        (((((((((((((((,                                        
                      //////((((((((((                                          
                    ////////////(((((                                           
                   *///// //////////                                            
                 ,*****///////////                                              
                ***********///****                                              
               ****** ***********                                               
             ******* ***********                                                
            ******* ******** **                                                 
           ******* **********                                                   
          *******,**********,                                                   
         *******************                                                    
        ******************,                                                     
        *****************                                                       
       ****************                                                         
       ,,************                                                           
    ,,.,,,*.*****   ,.                                                          
     ,,,,, ,,,,,,,,.                                                            
      ,,, ,,,,,,,,,                                                             
    ,,,, ,,,,,,                                                                 
      ,  ,                                                                      
     ,                                                                          
    ,                                                                           
    .                                                                           
   ,                                                                            
  .                                                                             
 .                                                                                                               
EOF
echo
echo " +---------------------------------------------------+"
echo " |                INSTALLING APACHE2                 |"
echo " +---------------------------------------------------+"
echo
sleep 1
zypper update -y 
zypper install apache2  -y
spinner $!
systemctl start apache2 -y
systemctl enable apache2 -y
systemctl status apache2 -y
done