function downloadAllOriginalFiles(version) {
  const originalFileLinks = document.querySelectorAll(`a[href^="versions/${version}/"]`);
  downloadLinks(originalFileLinks);
}

function downloadAllExtractedImages(version) {
  const extractedImageLinks = document.querySelectorAll(`a[href^="versions/${version}/extracted/"]`);
  downloadLinks(extractedImageLinks);
}

function downloadLinks(links) {
  for (const link of links) {
    const url = link.getAttribute("href");
    const filename = link.getAttribute("download");
    downloadFile(url, filename);
  }
}

function downloadFile(url, filename) {
  const link = document.createElement("a");
  link.href = url;
  link.download = filename;
  link.click();
}

// Attach the functions to the buttons
document.addEventListener("DOMContentLoaded", function () {
  const downloadOriginalButtons = document.querySelectorAll('[onclick^="downloadAllOriginalFiles"]');
  for (const button of downloadOriginalButtons) {
    const version = button.getAttribute("onclick").match(/\('([^']+)'\)/)[1];
    button.addEventListener("click", function () {
      downloadAllOriginalFiles(version);
    });
  }

  const downloadExtractedButtons = document.querySelectorAll('[onclick^="downloadAllExtractedImages"]');
  for (const button of downloadExtractedButtons) {
    const version = button.getAttribute("onclick").match(/\('([^']+)'\)/)[1];
    button.addEventListener("click", function () {
      downloadAllExtractedImages(version);
    });
  }
});
