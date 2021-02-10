function giveFeedback(show) {
    let feedback = document.getElementById("FeedbackWindow");
    let backdrop = document.getElementById("backdrop");
    if(show){
        backdrop.style.display = "block";
        feedback.style.display = "block";
        feedback.classList.remove("hiddenFeedbackWindow");
        feedback.classList.add("showFeedbackWindow");

    }
    else{
        feedback.style.display = "none";
        backdrop.style.display = "none";
        feedback.classList.remove("showFeedbackWindow");
        feedback.classList.add("hiddenFeedbackWindow");
    }
}