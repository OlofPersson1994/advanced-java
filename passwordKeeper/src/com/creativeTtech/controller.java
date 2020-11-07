package com.creativeTtech;
import java.util.*;
public class controller {


    String masterPassword = "password";
    String welcomeText = "Welcome to passwordKeeper.\nPlease put in your masterpassword.";
    String option = ("1: Print passwords\n2: Add new password\n3: Change your masterpassword.");
    int wrongMasterPasswordCounter = 2;
    boolean loggedOut = true;


    public controller() {
        passwordContainer passwordContainer = new passwordContainer();
        masterLogin();

        while (true) {

            System.out.println(option);
            Scanner menuScanner = new Scanner(System.in);
            int menuInput = menuScanner.nextInt();


            if (menuInput == 1) {

                System.out.println("Printing the list with passwords: \n");

               passwordContainer.printList(passwordContainer.list);

            }
            if (menuInput == 2) {

                System.out.println("Put in the new password: ");

                menuScanner = new Scanner(System.in);
                String addPasswordToList = menuScanner.nextLine();

                passwordContainer.list.add(addPasswordToList);
            }
            if(menuInput == 3){

                System.out.println("Here we will change your masterpassword, are your sure your want to do this? " +
                        "Type Y to change your masterpassword.");
                menuScanner = new Scanner(System.in);
                String changeMasterPasswordInput = menuScanner.nextLine();

                if(changeMasterPasswordInput.equalsIgnoreCase("Y")){
                    System.out.println("Type in your new masterpassword: ");
                    menuScanner = new Scanner(System.in);
                    masterPassword = menuScanner.nextLine();

                    System.out.println("Your new masterpassword is: "+ masterPassword);
                }
            }
        }
    }

    public void masterLogin(){

        System.out.println(welcomeText);

        while (loggedOut) {

            Scanner masterPasswordScanner = new Scanner(System.in);
            String masterPasswordInput = masterPasswordScanner.nextLine();

            if (masterPassword.equals(masterPasswordInput)) {
                System.out.println("You are logged in.");
                loggedOut = false;
            }

            else if (wrongMasterPasswordCounter == 0){
                System.out.println("Sorry your have put in the wrong masterpassword to many times," +
                        " all your password will now be deleted. Your masterpassword is now set back to default");
                System.exit(0);
            }

            else if (wrongMasterPasswordCounter != 0) {
                System.out.println("Wrong masterpassword, please try again. You have " + wrongMasterPasswordCounter +
                        " attempts left.");
                wrongMasterPasswordCounter--;
            }

        }

    }
}

