
import java.util.*;


public class MovieApp {
    private Set<Movie> movieSet = new TreeSet<>();
    private Set<User> userSet = new HashSet<>();
    public boolean addMovie(String title, String[] tags) {
        // TODO sub-problem 1
        if (findMovie(title) != null){ return false; }
        movieSet.add(new Movie(title, tags));
        return true;
    }

    public boolean addUser(String name) {
        // TODO sub-problem 1
        if (findUser(name) != null){ return false;}
        userSet.add(new User(name));
        return true;
    }

    public Movie findMovie(String title) {
        // TODO sub-problem 1
        if (title == null) { return null;}
        for (Movie movie : movieSet){
            if(movie.getTitle().compareTo(title) < 0){ continue;}
            if(movie.getTitle().equals(title)){ return movie; }
            break;
        }
        return null;
    }

    public User findUser(String username) {
        // TODO sub-problem 1
        if (username == null) { return null; }
        for(User user : userSet){
            if(user.getUsername().equals(username)){ return user; }
        }
        return null;
    }

    public List<Movie> findMoviesWithTags(String[] tags) {
        // TODO sub-problem 2
        List<Movie> result = new LinkedList<>();
        if(tags.length == 0){return result;}
        for (Movie movie: movieSet){
            String[] movieTags = movie.getTags();
            if(Arrays.asList(movieTags).containsAll(Arrays.asList(tags))){
                result.add(movie);
            }
        }
        return result;
    }

    public boolean rateMovie(User user, String title, int rating) {
        // TODO sub-problem 3
        Movie movie = findMovie(title);
        if (movie == null || !userSet.contains(user) || !(rating >= 1 && rating<=10)){
            return false;
        }
        movie.rateMovie(user, rating);
        return true;
    }

    public int getUserRating(User user, String title) {
        // TODO sub-problem 3
        Movie movie = findMovie(title);

        if (movie == null || !userSet.contains(user)){
            return -1;
        }
        return movie.getRating(user);
    }

    public List<Movie> findUserMoviesWithTags(User user, String[] tags) {
        // TODO sub-problem 4
        if(!userSet.contains(user)){
            return new LinkedList<>();
        }
        List<Movie> movies = findMoviesWithTags(tags);
        user.addSearchedMovies(movies);
        return movies;
    }

    public List<Movie> recommend(User user) {
        // TODO sub-problem 4
        if(!userSet.contains(user)){
            return new LinkedList<>();
        }
        return user.recommend();
    }
}
