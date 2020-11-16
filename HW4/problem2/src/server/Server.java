package server;

import course.*;
import exceptions.*;
import utils.Config;
import utils.ErrorCode;
import utils.Pair;
import java.io.File;

import java.io.IOException;
import java.util.*;
import java.nio.file.*;

public class Server {
    private static String coursesDir = "data/Courses/2020_Spring/";
    private static String usersDir = "data/Users/";
    private Map<Course, Set<String>> courseKeywordMap = new HashMap<>();
    private Set<User> users = new HashSet<>();

    public Server(){
        loadCourses();
        loadUsers();
    }

    private void loadCourses(){
        for (File collegeDir:(new File(coursesDir)).listFiles()){
            for(File courseFile:(collegeDir).listFiles()){
                try {
                    String[] content = Files.readString(courseFile.toPath()).split("\\|");
                    int courseId = Integer.parseInt(courseFile.getName().split("\\.")[0]);
                    String college = collegeDir.getName();
                    String department = content[0];
                    String academicDegree = content[1];
                    int academicYear = Integer.parseInt(content[2]);
                    String courseName = content[3];
                    int credit = Integer.parseInt(content[4]);
                    String location = content[5];
                    String instructor = content[6];
                    int quota = Integer.parseInt(content[7]);
                    Course course = new Course(courseId,college,department,academicDegree,academicYear,courseName,credit,location,instructor,quota);
                    courseKeywordMap.put(course, Set.of(courseName.split("\\s+")));
                } catch (IOException e) {
//                    e.printStackTrace();
                }
            }
        }
    }

    private void loadUsers(){
        for(File user:(new File(usersDir)).listFiles()){
            users.add(new User(user));
        }
    }

    private User findUser(String userId) throws UserIdNotFoundException {
        if (userId == null) {
            throw new UserIdNotFoundException("User id is null.");
        }
        for (User user : users){
            if(userId.equals(user.userId)){ return user; }
        }
        throw new UserIdNotFoundException(String.format("User id %s is not valid.",userId));
    }

    private Course findCourse(int coursesId) throws NoCourseIdException {
        for(Course course:courseKeywordMap.keySet()){
            if (coursesId == (course.courseId)){ return course;}
        }
        throw new NoCourseIdException(String.format("Course id %s is not valid.",coursesId));
    }

    private void sortCourses(List<Course> courses, String sortCriteria){
        if(sortCriteria == null || sortCriteria.equals("")){
            sortCourses(courses, "id");
            return;
        }
        switch (sortCriteria){
            case "id":
                Collections.sort(courses, new Comparator<Course>() {
                    @Override
                    public int compare(Course o1, Course o2) {
                        return o1.courseId - o2.courseId;
                    }
                });
                break;
            case "name":
                sortCourses(courses, "id");
                Collections.sort(courses, new Comparator<Course>() {
                    @Override
                    public int compare(Course o1, Course o2) {
                        return o1.courseName.compareTo(o2.courseName);
                    }
                });
                break;
            case "dept":
                sortCourses(courses, "id");
                Collections.sort(courses, new Comparator<Course>() {
                    @Override
                    public int compare(Course o1, Course o2) {
                        return o1.department.compareTo(o2.department);
                    }
                });
                break;
            case "ay":
                sortCourses(courses, "id");
                Collections.sort(courses, new Comparator<Course>() {
                    @Override
                    public int compare(Course o1, Course o2) {
                        return o1.academicYear - o2.academicYear;
                    }
                });
                break;
        }
    }


    public List<Course> search(Map<String,Object> searchConditions, String sortCriteria){
        // TODO Problem 2-1
        String dept = null;
        Integer ay = null;
        Set<String> keyWords = new HashSet<>();
        List<Course> searchedCourses = new ArrayList<>();
        if(searchConditions != null) {
            dept = (String) (searchConditions.get("dept"));
            ay = (Integer) (searchConditions.get("ay"));
            String name = (String)(searchConditions.get("name"));
            if(name != null){
                keyWords = Set.of(name.split("\\s+"));
            }
        }
        for(Course course:courseKeywordMap.keySet()){
            if (dept != null && !dept.equals(course.department)){
                continue;
            }
            if (ay != null && !ay.equals(course.academicYear)){
                continue;
            }
            if (!courseKeywordMap.get(course).containsAll(keyWords)){
                continue;
            }
            searchedCourses.add(course);
        }
        sortCourses(searchedCourses, sortCriteria);
        return searchedCourses;
    }

    public int bid(int courseId, int mileage, String userId){
        // TODO Problem 2-2
        try {
            User user = findUser(userId);
            Course course = findCourse(courseId);
            if(mileage < 0){
                throw new NegativeMileageException(String.format("%d is negative value",mileage ));
            }
            if(mileage > Config.MAX_MILEAGE_PER_COURSE){
                throw new OverMaxCourseMileageException(String.format("%d exceeds the maximum allowable mileage per course(%d)",mileage, Config.MAX_MILEAGE_PER_COURSE ));
            }
            user.bid(courseId, mileage);
        } catch (UserIdNotFoundException e) {
//            System.out.println(e.toString());
            return ErrorCode.USERID_NOT_FOUND;
        } catch (NoCourseIdException e) {
//            System.out.println(e.toString());
            return ErrorCode.NO_COURSE_ID;
        } catch (NegativeMileageException e) {
//            System.out.println(e.toString());
            return ErrorCode.NEGATIVE_MILEAGE;
        } catch (OverMaxCourseMileageException e) {
//            System.out.println(e.toString());
            return ErrorCode.OVER_MAX_COURSE_MILEAGE;
        } catch (OverMaxMileageException e) {
//            System.out.println(e.toString());
            return ErrorCode.OVER_MAX_MILEAGE;
        } catch (IOException e) {
//            e.printStackTrace();
            return ErrorCode.IO_ERROR;
        }
        return ErrorCode.SUCCESS;
    }

    public Pair<Integer,List<Bidding>> retrieveBids(String userId){
        // TODO Problem 2-2
        int errorCode = ErrorCode.SUCCESS;
        List<Bidding> bids = new ArrayList<>();
        try {
            User user = findUser(userId);
            bids = user.retrieveBids();
        } catch (UserIdNotFoundException e) {
//            System.out.println(e.toString());
            errorCode = ErrorCode.USERID_NOT_FOUND;
        } catch (IOException e) {
//            e.printStackTrace();
            errorCode = ErrorCode.IO_ERROR;
        }

        return new Pair<>(errorCode,bids);
    }

    public boolean confirmBids(){
        // TODO Problem 2-3
        try {
            for (User user : users) {
                    user.registeredCourses = new ArrayList<>();
                }
            for (Course course : courseKeywordMap.keySet()) {
                int coursesId = course.courseId;
                int quota = course.quota;
                List<Pair<User, Integer>> userMileages = new ArrayList<>();
                for (User user : users) {
                    int mileage = user.retrieveBid(coursesId);
                    if (mileage != 0) {
                        userMileages.add(new Pair<User,Integer>(user, mileage));
                    }
                }
                Collections.sort(userMileages, new Comparator<Pair<User, Integer>>() {
                    @Override
                    public int compare(Pair<User, Integer> o1, Pair<User, Integer> o2) {
                        User user1 = o1.key;
                        User user2 = o2.key;
                        int mileage1 = o1.value;
                        int mileage2 = o2.value;
                        int mileageSum1 = user1.mileageSum;
                        int mileageSum2 = user2.mileageSum;
                        if(mileage1 != mileage2){
                            return mileage2 - mileage1;
                        }else if(mileageSum1 != mileageSum2){
                            return mileageSum1 - mileageSum2;
                        }else {
                            return o1.key.userId.compareTo(o2.key.userId);
                        }
                    }
                });
                for(int i = 0; i < Math.min(userMileages.size(),quota); i++){
                    Pair<User, Integer> userMileage = userMileages.get(i);
                    User user = userMileage.key;
                    user.registeredCourses.add(course);
                }
            }
        } catch (IOException e) {
//            e.printStackTrace();
            return false;
        }
        return true;
    }

    public Pair<Integer,List<Course>> retrieveRegisteredCourse(String userId){
        // TODO Problem 2-3
        int errorCode = ErrorCode.SUCCESS;
        List<Course> registeredCourses = new ArrayList<>();
        try {
            User user = findUser(userId);
            registeredCourses = user.retrieveRegisteredCourses();
        } catch (UserIdNotFoundException e) {
//            System.out.println(e.toString());
            errorCode = ErrorCode.USERID_NOT_FOUND;
        } catch (IOException e){
//            e.printStackTrace();
            errorCode = ErrorCode.IO_ERROR;
        }

        return new Pair<>(errorCode,registeredCourses);

    }
}