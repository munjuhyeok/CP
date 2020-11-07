package cpta;

import cpta.environment.Compiler;
import cpta.environment.Executer;
import cpta.exam.ExamSpec;
import cpta.exam.Problem;
import cpta.exam.Student;
import cpta.exam.TestCase;
import cpta.exceptions.CompileErrorException;
import cpta.exceptions.FileSystemRelatedException;
import cpta.exceptions.InvalidFileTypeException;
import cpta.exceptions.RunTimeErrorException;

import javax.management.RuntimeErrorException;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Array;
import java.nio.file.*;
import java.util.*;

public class Grader {
    Compiler compiler;
    Executer executer;

    private boolean equals(String file1, String file2){
        try {
            String f1 = Files.readString(Paths.get(file1));
            String f2 = Files.readString(Paths.get(file2));
            return f1.equals(f2);
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    private boolean equals(String file1, String file2, Set<String> judgingTypes){
        try {
            String f1 = Files.readString(Paths.get(file1));
            String f2 = Files.readString(Paths.get(file2));
            if(judgingTypes.contains(Problem.IGNORE_WHITESPACES)){
                f1 = f1.replaceAll("\\s", "");
                f2 = f2.replaceAll("\\s", "");
            }else if(judgingTypes.contains(Problem.TRAILING_WHITESPACES)){
                f1 = f1.replaceAll("\\s+$","");
                f2 = f2.replaceAll("\\s+$","");
            }
            if(judgingTypes.contains(Problem.CASE_INSENSITIVE)){
                return f1.equalsIgnoreCase(f2);
            }else {
                return f1.equals(f2);
            }
        } catch (IOException e) {
            return false;
        }
    }

    private void copyFiles(String sourceDir, String destDir) {
        File s = new File(sourceDir);
        try {
            for(File file:s.listFiles()){
                File d = new File(destDir + file.getName());
                Files.copy(file.toPath(), d.toPath(), StandardCopyOption.REPLACE_EXISTING);
            }
        } catch (IOException e) {
            System.out.println(String.format("Cannot copy files from %s to %s", sourceDir, destDir));
        }
    }

    private String extractFileType(File file){
        String[] pieces = file.getName().split("\\.");
        if(pieces.length == 2){
            return pieces[1].toLowerCase();
        }
        return null;
    }

    public Grader(Compiler compiler, Executer executer) {
        this.compiler = compiler;
        this.executer = executer;
    }

    public Map<String,Map<String, List<Double>>> gradeSimple(ExamSpec examSpec, String submissionDirPath) {
        // TODO Problem 1-1
        Map<String,Map<String, List<Double>>> scoresOfAllStudents = new HashMap<>();
        List<Problem> problems = examSpec.problems;
        List<Student> students = examSpec.students;
        for(Student student:students){
            String studentId = student.id;
            Map<String, List<Double>> scoresOfStudent = new HashMap<>();
            for(Problem problem:problems){
                String problemId = problem.id;
                String testCasesDirPath = problem.testCasesDirPath;
                List<TestCase> testCases = problem.testCases;
                String sugoFileName = problem.targetFileName;
                String yoFileName = sugoFileName.split("\\.")[0]+".yo";
                String testCaseDirPath = problem.testCasesDirPath;
                String problemPath = submissionDirPath + studentId + "/" + problemId + "/";
                List<Double> problemScores = new ArrayList<>();
                try {
                    compiler.compile(problemPath + sugoFileName);
                }catch (CompileErrorException e){
                    e.printStackTrace();
                }catch (InvalidFileTypeException e){
                    e.printStackTrace();
                }catch (FileSystemRelatedException e){
                    e.printStackTrace();
                }
                for(TestCase testCase:testCases){
                    String testCaseId = testCase.id;
                    String inputFileName = testCase.inputFileName;
                    String outputFileName = testCase.outputFileName;
                    double score = testCase.score;
                    try {
                        executer.execute(problemPath + yoFileName, testCaseDirPath + inputFileName, problemPath + testCaseId);
                    } catch (RunTimeErrorException e) {
                        continue;
                    } catch (FileSystemRelatedException e) {
                        e.printStackTrace();
                    } catch (InvalidFileTypeException e) {
                        e.printStackTrace();
                    }
                    if(equals(testCaseDirPath + outputFileName, problemPath + testCaseId)) {
                        problemScores.add(score);
                    }else{
                        problemScores.add(0.0);
                    }
                }
                scoresOfStudent.put(problemId, problemScores);
            }
            scoresOfAllStudents.put(studentId, scoresOfStudent);
        }
        return scoresOfAllStudents;
    }

    public Map<String,Map<String, List<Double>>> gradeRobust(ExamSpec examSpec, String submissionDirPath) {
        // TODO Problem 1-2
        Map<String,Map<String, List<Double>>> scoresOfAllStudents = new HashMap<>();
        List<Problem> problems = examSpec.problems;
        List<Student> students = examSpec.students;
        (new File(submissionDirPath)).listFiles();
        for(Student student:students){
            String studentId = student.id;
            boolean noSubmission = false;
            String studentPath = submissionDirPath + studentId;
//            if(!(new File(studentPath)).exists()){
//
//            }
            Map<String, List<Double>> scoresOfStudent = new HashMap<>();
            for(Problem problem:problems){
                String problemId = problem.id;
                String testCasesDirPath = problem.testCasesDirPath;
                List<TestCase> testCases = problem.testCases;
                String targetSugoFileName = problem.targetFileName;
                String targetYoFileName = targetSugoFileName.split("\\.")[0]+".yo";
                String wrappersDirPath = problem.wrappersDirPath;
                Set<String> judgingTypes = problem.judgingTypes;
                String testCaseDirPath = problem.testCasesDirPath;
                String problemPath = studentPath + "/" + problemId + "/";
                List<Double> problemScores = new ArrayList<>();
                boolean compileFail = false;
                boolean halfScore = false;
                if(wrappersDirPath != null){
                    copyFiles(wrappersDirPath, problemPath);
                }
                if((new File(problemPath)).exists()) {
                    File[] fileList = (new File(problemPath)).listFiles();
                    for (File file : fileList) {
                        if("yo".equals(extractFileType(file)) && !(new File(file.toString().replace("yo","sugo")).exists())){
                            halfScore = true;
                        }
                        if("sugo".equals(extractFileType(file))) {
                            try {
                                compiler.compile(file.toString());
                            } catch (CompileErrorException e) {
                                for(TestCase testCase:testCases){
                                    problemScores.add(0.0);
                                }
                                scoresOfStudent.put(problemId, problemScores);
                                System.out.println("Failed to compile " + file.toString());
                                compileFail = true;
                                break;
                            } catch (InvalidFileTypeException e) {
                                e.printStackTrace();
                            } catch (FileSystemRelatedException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                }
                if(compileFail){
                    continue;
                }
                for(TestCase testCase:testCases){
                    String testCaseId = testCase.id;
                    String inputFileName = testCase.inputFileName;
                    String outputFileName = testCase.outputFileName;
                    double score = halfScore? testCase.score/2 : testCase.score;
                    try {
                        executer.execute(problemPath + targetYoFileName, testCaseDirPath + inputFileName, problemPath + testCaseId);
                    } catch (RunTimeErrorException e) {
                        problemScores.add(0.0);
                        System.out.println("Failed to execute " + problemPath + targetYoFileName + " with " + testCaseDirPath + inputFileName);
                        continue;
                    } catch (FileSystemRelatedException e) {
                        e.printStackTrace();
                    } catch (InvalidFileTypeException e) {
                        e.printStackTrace();
                    }
                    if(equals(testCaseDirPath + outputFileName, problemPath + testCaseId, judgingTypes)) {
                        problemScores.add(score);
                    }else{
                        problemScores.add(0.0);
                    }
                }
                scoresOfStudent.put(problemId, problemScores);
            }
            scoresOfAllStudents.put(studentId, scoresOfStudent);
        }
        return scoresOfAllStudents;
    }

}

