document.addEventListener("DOMContentLoaded", function() {
	const downloadOriginalButtons = document.querySelectorAll('[onclick^="downloadAllOriginalFiles"]');
	for (const button of downloadOriginalButtons) {
		const version = button.getAttribute("onclick").match(/\('([^']+)'\)/)[1];
		button.addEventListener("click", function() {
			downloadAllOriginalFiles(version);
		});
	}

	const downloadExtractedButtons = document.querySelectorAll('[onclick^="downloadAllExtractedImages"]');
	for (const button of downloadExtractedButtons) {
		const version = button.getAttribute("onclick").match(/\('([^']+)'\)/)[1];
		button.addEventListener("click", function() {
			downloadAllExtractedImages(version);
		});
	}
});
