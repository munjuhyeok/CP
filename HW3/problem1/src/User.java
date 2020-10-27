

import java.util.*;

public class User{
    public String getUsername() {
        return username;
    }

    private String username;



    public LinkedList<Movie> recommend(){
        LinkedList<Movie> recommendedMovies = new LinkedList<>();
        for (Movie movie : searchedMovies) {
            double rating = movie.getAverageRating();
            int size = recommendedMovies.size();
            if (size < 1 || rating > recommendedMovies.get(0).getAverageRating()) {
                recommendedMovies.add(0, movie);
            } else if (size < 2 || rating > recommendedMovies.get(1).getAverageRating()) {
                recommendedMovies.add(1, movie);
            } else if (size < 3 || rating > recommendedMovies.get(2).getAverageRating()) {
                recommendedMovies.add(2, movie);
            }
            size = recommendedMovies.size();
            if (size == 4) { recommendedMovies.remove(3); }

        }
        return recommendedMovies;
    }
    public void addSearchedMovies(List<Movie> movies){
        searchedMovies.addAll(movies);
    }

    private TreeSet<Movie> searchedMovies = new TreeSet<>();

    public User(String username) { this.username = username; }
    @Override
    public String toString() {
        return username;
    }
}
