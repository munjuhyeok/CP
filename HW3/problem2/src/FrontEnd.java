import java.util.*;
import java.time.LocalDateTime;

public class FrontEnd {
    private UserInterface ui;
    private BackEnd backend;
    private User user;

    public FrontEnd(UserInterface ui, BackEnd backend) {
        this.ui = ui;
        this.backend = backend;
    }
    
    public boolean auth(String authInfo){
        // TODO sub-problem 1
        String[] idPasswd = authInfo.split("\\n");
        String id;
        String passwd;
        try{
            id = idPasswd[0];
        }catch (ArrayIndexOutOfBoundsException e){
            id = "";
        }
        try{
            passwd = idPasswd[1];
        }catch (ArrayIndexOutOfBoundsException e){
            passwd = "";
        }
        if(backend.auth(id, passwd)){
            user = new User(id, passwd);
            return true;
        }
        return false;
    }

    public void post(Pair<String, String> titleContentPair) {
        // TODO sub-problem 2
        String title = titleContentPair.key;
        String content = titleContentPair.value;
        backend.post(new Post(title, content));
    }
    
    public void recommend(){
        // TODO sub-problem 3
        List<Post> recommendedPostList = backend.recommend();
        Iterator<Post> postIterator= recommendedPostList.iterator();
        while (postIterator.hasNext()){
            Post post = postIterator.next();
            ui.println(post.toString());
        }
    }

    public void search(String command) {
        // TODO sub-problem 4
        Set<String> keywords = new HashSet<>();
        String [] duplicateKeywords = command.split("\\s+");
        for (int i = 1; i< duplicateKeywords.length; i++){
            keywords.add(duplicateKeywords[i]);
        }
        List<Post> searchedPostList = backend.search(keywords);
        Iterator<Post> postIterator= searchedPostList.iterator();
        while (postIterator.hasNext()){
            Post post = postIterator.next();
            ui.println(post.getSummary());
        }
    }
    
    User getUser(){
        return user;
    }
}
