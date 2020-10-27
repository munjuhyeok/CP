import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

public class BackEnd extends ServerResourceAccessible {
    // Use getServerStorageDir() as a default directory
    // TODO sub-program 1 ~ 4 :
    String serverStorageDir = getServerStorageDir();
    String userId;
    private final static DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

    public boolean auth(String id, String password){
        File file = new File(serverStorageDir + id + "/password.txt");
        String correctPasswd;
        try {
            Scanner input = new Scanner(file);
            try {
                correctPasswd = input.nextLine();
            } catch (final NoSuchElementException ex) {
                correctPasswd = "";
            }
        } catch (FileNotFoundException e) {
            correctPasswd = null;
        }
        if(password.equals(correctPasswd)){
            userId = id;
            return true;
        }
        return false;
    }

    public void post(Post post) {
        // TODO sub-problem 2
        File postPath = new File(serverStorageDir + userId + "/post/");
        String[] postIds = postPath.list();
        int postId = Integer.parseInt(Collections.max(Arrays.asList(postIds)).split("[.]")[0]) + 1;
        post.setId(postId);
        String date = post.getDate();
        String title = post.getTitle();
        String content = post.getContent();
        try {
            FileWriter fileWriter = new FileWriter(postPath.toString() + "/" + postId + ".txt");
            fileWriter.write(date+"\n");
            fileWriter.write(title+"\n\n");
            fileWriter.write(content);
            fileWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public List<Post> recommend() {
        File friendList = new File(serverStorageDir + userId + "/friend.txt");
        List<Post> posts = new LinkedList<>();
        List<LocalDateTime> times = new LinkedList<>();

        try {
            Scanner input = new Scanner(friendList);
            while(input.hasNext()) {
                    String friend = input.nextLine();
                    File friendPostPath = new File(serverStorageDir + friend + "/post/");
                    for (File post : friendPostPath.listFiles()){
                        Scanner postReader = new Scanner(post);
                        int numRecommended = posts.size();
                        LocalDateTime time = Post.parseDateTimeString(postReader.nextLine(), formatter);
                        for (int i=0; i<10; i++){
                            if(numRecommended == i || time.isAfter(times.get(i))){
                                int id = Integer.parseInt(post.getName().split("[.]")[0]);
                                String title = postReader.nextLine();
                                String content = "";
                                while(postReader.hasNext()){
                                    content += "\n" + postReader.nextLine();
                                }
                                posts.add(i, new Post(id, time, title, content));
                                times.add(i, time);
                                break;
                            }
                        }
                        if (posts.size() == 11) {
                            posts.remove(10);
                            times.remove(10);

                        }
                    }
            }
        } catch (FileNotFoundException e) {
        }
        return posts;
    }
    public List<Post> search(Set<String> keywords){
        File[] users = (new File(serverStorageDir)).listFiles();
        List<Post> posts = new LinkedList<>();
        List<LocalDateTime> times = new LinkedList<>();
        List<Integer> occurrences = new LinkedList<>();
        for (File user : users){
            File postPath = new File(user + "/post/");
            for (File post : postPath.listFiles()) {
                try{
                    Scanner postReader = new Scanner(post);
                    int numSearched = posts.size();
                    LocalDateTime time = Post.parseDateTimeString(postReader.nextLine(), formatter);
                    String title = postReader.nextLine();
                    String content = "";
                    while (postReader.hasNext()) {
                        content += "\n" + postReader.nextLine();
                    }
                    int occurrence = 0;
                    List<String> splitTitle = Arrays.asList(title.split("\\s"));
                    List<String> splitContent = Arrays.asList(content.split("\\s"));
                    for (String keyword : keywords){
                        occurrence += Collections.frequency(splitTitle, keyword);
                        occurrence += Collections.frequency(splitContent, keyword);
                    }
                    if(occurrence == 0) {continue;}
                    for (int i = 0; i < 10; i++) {
                        if (numSearched == i ) {
                            int id = Integer.parseInt(post.getName().split("[.]")[0]);
                            posts.add(i, new Post(id, time, title, content));
                            times.add(i, time);
                            occurrences.add(i, occurrence);
                            break;
                        }else {
                            int occurrenceOfI = occurrences.get(i);
                            LocalDateTime timeOfI = times.get(i);
                            if(occurrence > occurrenceOfI || (occurrence == occurrenceOfI && time.isAfter(timeOfI))) {
                                int id = Integer.parseInt(post.getName().split("[.]")[0]);
                                posts.add(i, new Post(id, time, title, content));
                                times.add(i, time);
                                occurrences.add(i, occurrence);
                                break;
                            }
                        }
                    }
                    if (posts.size() == 11) {
                        posts.remove(10);
                        times.remove(10);
                        occurrences.remove(10);
                    }
                }catch (FileNotFoundException e){

                }

            }
        }
        return posts;
    }

    // Create helper funtions to support FrontEnd class
}
