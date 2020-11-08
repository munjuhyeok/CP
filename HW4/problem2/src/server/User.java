package server;

import course.Bidding;
import course.Course;
import exceptions.OverMaxCourseMileageException;
import exceptions.OverMaxMileageException;
import exceptions.UserIdNotFoundException;
import utils.Config;
import utils.Pair;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class User {
    private String userPath;
    public String userId;
    public List<Bidding> bids;
    public List<Course> registeredCourses;
    File user;
    int mileageSum;
    public User(File user) {
        this.user = user;
        userPath = user.toString();
        this.userId = user.getName();
        loadBids();
    }

    private void loadBids(){
        try {
            Scanner scanner = new Scanner(new File(user, "bid.txt"));
            bids = new ArrayList<>();
            mileageSum = 0;
            while (scanner.hasNext()) {
                String line = scanner.nextLine();
                String[] idAndMileage = line.split("\\|");
                int courseId = Integer.parseInt(idAndMileage[0]);
                int mileage = Integer.parseInt(idAndMileage[1]);
                bids.add(new Bidding(courseId, mileage));
                mileageSum += mileage;
            }
            scanner.close();
        } catch (IOException e) {
            System.out.println(String.format("%s does not have bid.txt",userId));
        }

    }

    private void saveBids(){
        try {
            FileWriter fileWriter = new FileWriter(userPath+"/bid.txt");
            for (Bidding bidding : bids) {
                fileWriter.write(String.format("%d|%d\n",bidding.courseId, bidding.mileage ));
            }
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void bid(int courseId, int mileage) throws OverMaxMileageException, IOException {
        loadBids();
        int newMileageSum;
        if(bids == null){
            throw new IOException(String.format("There is no bids.txt under %s",userId));
        }
        for(Bidding bidding : bids){
            if(courseId == bidding.courseId){
                newMileageSum = mileageSum + mileage - bidding.mileage;
                if(newMileageSum > Config.MAX_MILEAGE){
                    throw new OverMaxMileageException(String.format("%d exceeds the maximum allowable mileage(%d)",newMileageSum, Config.MAX_MILEAGE));
                }
                if(mileage == 0){
                    bids.remove(bidding);
                }else {
                    bidding.mileage = mileage;
                }
                mileageSum = newMileageSum;
                saveBids();
                return;
            }
        }
        newMileageSum = mileageSum + mileage;
        if(newMileageSum > Config.MAX_MILEAGE){
            throw new OverMaxMileageException(String.format("%d exceeds the maximum allowable mileage(%d)",newMileageSum, Config.MAX_MILEAGE));
        }
        if(mileage != 0) {
            bids.add(new Bidding(courseId, mileage));
        }
        mileageSum = newMileageSum;
        saveBids();
    }

    public List<Bidding> retrieveBids() throws IOException {
        loadBids();
        if(bids == null){
            throw new IOException(String.format("There is no bids.txt under %s",userId));
        }
        return bids;
    }


    public int retrieveBid(int courseId) throws IOException {
        loadBids();
        if(bids == null){
            throw new IOException(String.format("There is no bids.txt under %s",userId));
        }
        for (Bidding bidding : bids){
            if(courseId == bidding.courseId) {
                bids.remove(bidding);
                saveBids();
                return bidding.mileage;
            }
        }
        return 0;
    }

    public List<Course> retrieveRegisteredCourses() throws IOException {
        loadBids();
        if(bids == null){
            throw new IOException(String.format("There is no bids.txt under %s",userId));
        }
        return registeredCourses;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof User){
            return userId == ((User)obj).userId;
        }else{
            return false;
        }
    }
}


