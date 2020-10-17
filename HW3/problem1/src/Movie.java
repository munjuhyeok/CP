
import java.util.HashMap;
import java.util.Map;

public class Movie implements Comparable<Movie>{
    public String getTitle() {
        return title;
    }

    private String title;

    public String[] getTags() {
        return tags;
    }

    private String[] tags;

    private Map<User, Integer> ratingMap = new HashMap<>();

    public Movie(String title) { this.title = title;}

    public Movie(String title, String[] tags) {
        this.title = title;
        this.tags = tags;
    }

    public void rateMovie(User user, int rating){
        ratingMap.put(user, rating);
    }

    public int getRating(User user){
        if(!ratingMap.containsKey(user)){ return 0; }
        return ratingMap.get(user);
    }

    public double getAverageRating(){
        if(ratingMap.size() == 0) { return 0; }
        int sum = 0;
        for(int rating : ratingMap.values()){
            sum += rating;
        }
        return (double)sum/ratingMap.size();
    }

    @Override
    public String toString() {
        return title;
    }

    @Override
    public int compareTo(Movie movie){
        return this.title.compareTo(movie.title);
    }
}
