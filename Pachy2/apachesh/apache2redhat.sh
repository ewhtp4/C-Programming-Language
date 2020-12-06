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
yum update -y 
yum install httpd -y
spinner $!
chkconfig httpd on -y
system-config-services -y
service httpd start
systemctl status httpd
done